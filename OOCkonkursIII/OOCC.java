import java.io.*;
import java.nio.charset.Charset;
import java.util.*;
import static javafx.application.Platform.exit;

class tools{
    static FileInputStream source = null;
    static boolean openfile(String path){
        try {
            source = new FileInputStream(path);
        } catch (FileNotFoundException ex) {
            System.out.print("Nie znaleziono pliku!");
            return false;
        }
        if(OOCC.DEBUG_MODE){
            System.out.println("Plik poprawnie załadowany");
        }
        return true;
    }
    static void fileToData(FileInputStream fis, List<data>pdata){
        BufferedReader br = new BufferedReader(new InputStreamReader(fis, Charset.forName("UTF-8")));
        String temp;
        try {
            while((temp = br.readLine()) != null){
                String[] split = temp.split(",");
                if(split.length != 5){
                    System.out.println("Błąd w pliku wejściowym");
                    exit();
                }
                data tdata = new data(split[0], Integer.parseInt(split[1]), Integer.parseInt(split[2]), Integer.parseInt(split[3]), Integer.parseInt(split[4]));
                pdata.add(tdata);
            }
        } catch (IOException ex) {
            System.out.println("Błąd przy czytaniu pliku.");
        }
    }
    static double calctime(data from, data to){
        return Math.sqrt(Math.pow(to.xpos - from.xpos, 2) + Math.pow(to.ypos-from.ypos, 2)) + to.time;
    }
}

class data{
    String id;
    int xpos;
    int ypos;
    int time;
    int satisfaction;
    boolean used;

    data(String s, int i, int i0, int i1, int i2) {
        this.id = s;
        this.xpos = i;
        this.ypos = i0;
        this.time = i1;
        this.satisfaction= i2;
        this.used = false;
    }
}

public class OOCC {
    static final boolean DEBUG_MODE = true;
    public static void main(String[] args) {
        double totaltime = 0;
        if(args.length == 0){
            System.out.println("nie podano argumentu");
            System.exit(1);
        }
        if(!tools.openfile(args[0])){
            System.exit(0);
        }
        String output;
        //pdata ptrzetrzymuje wszystkie rekordy w załadowanym pliku
        List<data> pdata = new ArrayList<data>();
        // pdata jest typu "data", funkcja ponizej zaladuje odpowiednie wartości do odpowiadających im pól
        tools.fileToData(tools.source, pdata);
        //pierwszy element tablicy data to element, w ktorym zaczynamy i konczymy podróż
        data posnow = pdata.get(0);
        output = pdata.get(0).id + ",";

         while (true) {
             //sdata będzie przetrzymywać dane posortowane w sposób satysfakcja/czas dojścia
             List<data> sdata = new ArrayList<data>();

             //--------------------------------------------------------
             for (data i : pdata) {
                 if(sdata.size() > 0) {
                     for (int j = 0; j < sdata.size(); j++){
                         if(tools.calctime(posnow, i) > tools.calctime(posnow, sdata.get(j))){
                             sdata.add(j, i);
                             break;
                         }
                     }
                 }
                 else{
                     sdata.add(i);
                 }
             }
             //--------------------------------------------------------
             //cała ta pętla sortuje tablicę sdata po satysfakcji wynikowej
             //
             //teraz sprawdzamy, czy w danym punkcie już byliśmy, i jeśli nie, to czy z tego punktu da się wrócić spowrotem
             //do punktu startowego. Jeśli nie da się już wrócić, jest to ostatni punkt i powracamy na początek i zakańczamy
             //program
             boolean stepend = true;
             for(data i: sdata){
                 //szukamy pdata z tym samym id co sdata
                 boolean isused = false;
                 for(data g: pdata){
                     if (g.id.equals(i.id)){
                         if (g.used){
                             //jeśli pdata z tym samym id już była używana, ustawiamy flagę
                             isused = true;
                         }
                         else{
                             break;
                         }
                     }
                 }
                 //jeśli flaga ustawiona, kontynuacja pętli
                 if(isused){
                     continue;
                 }
                 if(600 >= totaltime + tools.calctime(posnow, i) + tools.calctime(i, pdata.get(0))){
                     System.out.println(i.time);
                     output += i.id + ",";
                     stepend =  false;
                     posnow = i;
                     totaltime += tools.calctime(posnow, i);
                     //tak samo jak wyżej szukamy pdata z tym samym id aby ustawić flagę
                     for(data g: pdata){
                         if(g.id.equals(i.id)){
                             g.used = true;
                         }
                     }
                     break;
                 }
             }
             //jeśli powyższa pętla nie zrobi kroku, tj. nie ma już miejsca z którego można wrócić na start lub
             //wszystkie miejsca są użyte, to dodajemy na koniec listy początek i zakańczamy działanie programu

             if (stepend){
                 break;
             }
        }

        //i zapisujemy wynik do pliku :)
        if(DEBUG_MODE){
             float sumtimedbg =0;
             float sumscoredbg =0;
             String each[] = output.split(",");
             for(data g: pdata){
                 for(String c: each){
                     if(g.id.equals(c)){
                         sumtimedbg+=g.time;
                         sumscoredbg+=g.satisfaction;
                     }
                 }
             }
             System.out.println(sumscoredbg);
             System.out.println(totaltime);
             System.out.println(sumtimedbg);
        }
        try{
            PrintWriter writer = new PrintWriter("result.csv", "UTF-8");
            writer.println(output);
            writer.close();
        } catch (IOException e) {
             System.out.println("Nie udało się zapisać pliku");
        }
    }
}