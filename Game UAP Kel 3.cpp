/*=====================================================================================================
* Game sederhana berbasis teks
* dibuat oleh : 
* 	Auvar Mahsa Fahlevi
* 	Cindy Loria
* 	Siti Ayuni
*
*
* compile g++ Game UAP Kel 3.cpp -o Game UAP Kel 3 -lncurses
*=====================================================================================================*/
#include<ncurses.h> 	//library untuk mengatur tulisan pada terminal
#include<windows.h> 	//library untuk menggunakan pemberian warna pada kalimat dan background serta peletakan posisi
using namespace std; 	//agar tidak menulis std berulangkali
#define KEY_ESC 27 		//mendefinisikan tombol ESC nilai 27
	
	char namap[50], player[10] = "-o-"; //karakter
	int x = 1, y = 1; 					//posisi awal pada window
	int point = 0; 						//nilai awal movement
	
	
	//mvprintw digunakan untuk menuliskan string dan mengatur posisi
	//menu untuk memasukkan username
	void nama(){
		mvprintw(7, 10,  "+===================================================================================================+\n");
		mvprintw(8, 10,  "|========================================<<<<[GetOut]>>>>===========================================|\n");
		mvprintw(9, 10,  "	 			Username :  ");getstr(namap);
		clear(); //membersihkan layar
	}
	
	
	//petunjuk apa yang harus dilakukan pada game ini
	void petunjuk(){
		mvprintw(10, 13, "Intruksi >> Pemain Harus menemukan pintu keluar untuk menang melalui obstacle yang ada\n    ");
		mvprintw(12, 13, " 	*Hati-hati saat mencari pintu keluar.....\n    ");
		mvprintw(20, 11, "Press any key to next..."); 
		getch(); //menahan layar agar tidak langsung tertutup atau menunggu input dari keyboard
		clear();
	}
	
	
	//tampilan loading screen dengan menggunakan animasi
	void loading(){
	
	printw("Loading...\n"); //printw untuk menuliskan string pada layar
	
	printw("====================================================================================================\n");	
	for(int i = 1;i <= 100; i++){
		printw("|");
		refresh(); 			//menyegarkan layar 
		Sleep(20); 			//sebagai timer animasi (ms) 1000ms = 1s
	}	
	
	clear();
	}
	
	
	//map atau peta yang akan dioutputkan pada window
	void wall(WINDOW * win){
		mvwprintw(win, 1, 1,  "      []    [][][][][]            [ ]         [][][][][][           []      [][][]                ");
		mvwprintw(win, 2, 1,  "            []      []    []   [      ][][]   []                []      []    []    [][][][][]  []");
		mvwprintw(win, 3, 1,  "      []            []         []    []       []    [][]  [][]      []         [][]   []        []");
		mvwprintw(win, 4, 1,  "      []    []      []    []   []    []    ][][][]              []      []  []    []       []   []");
		mvwprintw(win, 5, 1,  "      []    []      []               []        []   []    []    []      []  []  []    []   []     ");
		mvwprintw(win, 6, 1,  "            []            []       ][][][][]   []       [][][]      []  []      []  [][]   []  [] ");
		mvwprintw(win, 7, 1,  "[ ][][][][][][]      []    []   [                   []          []  []  []  []  []  []     []     ");
		mvwprintw(win, 8, 1,  "                    []         []  []  [][]  []   [][][]      [][]          []           [][][][  ");
		mvwprintw(win, 9, 1,  "      []    []      []    []   []            []                     [][][]      []  [][][][][]    ");
		mvwprintw(win, 10, 1, "      []    []            []            [][][][]  [][][]    [][][]          []  []  []            ");
		mvwprintw(win, 11, 1, "      []    []      []  []    [][]  []                  []      []  [][][]               [][]   []");
		mvwprintw(win, 12, 1, "   [][][]  [][][][][][][]           []      [][][][][]   [][][]             []    [][]    []    []");
		mvwprintw(win, 13, 1, "               [][            [][]  []  []                 []   []    [][]  []      []          []");
		mvwprintw(win, 14, 1, "      []            []  []      []      [][][]  []  []          []      []      []  [][]  [][     ");
		mvwprintw(win, 15, 1, "      []    []      []  []          []              []   [][][] []  []  []  [][][]        [   ]   ");
		mvwprintw(win, 16, 1, "      []    []              [][]    [][]  [][][][]  []   []         []      []      [][]  [   ]   ");
		mvwprintw(win, 17, 1, "            []      []  [][][][][]                       []     []  []  []  []      []            ");
		mvwprintw(win, 18, 1, "[][][][][][][][][]      []          []    [][]  [][][]        [][]      []      []       [][]   []");
		wrefresh(win); //menyegarkan layar pada window
	}
	
	
	
	//===============================================================================================
	
	//FINISH 
	void finish(WINDOW * win){
		wclear(win);
		mvwprintw(win, 9,  40, "[You Win...]");
		mvwprintw(win, 10, 40, "[Total Move %i]", point);
		mvwprintw(win, 12, 20, "Play Again? Press any button but not the same button...");
		wgetch(win);
		wclear(win);
	}
	
	int done(WINDOW * win){
		if( x == 95 &&  y == 18 ){
			return 1;	//seluruh program telah selesai dan ke step selanjutnya
		}
		return 0;		//seluruh program telah selesai
	}	 
	
	int done2(WINDOW * win){
		if( x == 38 &&  y == 16 ){
			return 1;
		}
		return 0;
	}
		 
	//===============================================================================================
	
	//Game Over
	void over(WINDOW * win){
		wclear(win);
		mvwprintw(win, 9,  40, "[Game Over...]");
		mvwprintw(win, 10, 40, "[Total Move %i]", point);
		mvwprintw(win, 12, 20, "Play Again? Press any button but not the same button...");
		wgetch(win);
		wclear(win);
	}
	
	int end(WINDOW * win){
		if( (x <= 16) &&  y == 7 ){
			return 1;
		}
		return 0;
	}	 
	
	int end2(WINDOW * win){
		if( (x == 33 || x == 35 || x == 34)&&  y == 1 ){
			return 1;
		}
		return 0;
	}	 
	
	//===============================================================================================
	
	//melakukan deklarasi dua fungsi kedalam satu fungsi
	int start(){
		nama();
		petunjuk();
	}
	

	
int main(){
	initscr(); //fungsi untuk memulai mode ncurses
	
	start:
		point = 0; 	//mereset total movement saat game over atau finish
		start(); 	//output nama dan petunjuk yang sudak dideklarasikan pada int start
		clear();
	
	
	loading(); //output loading
	
		
	WINDOW * win = newwin(20, 100, 3, 10); 	//mengatur ukuran window dan posisi window pada saat di output
	refresh(); 								//menyegarkan layar 
	
	
	box(win, 1, 1); //membuat box atau garis tepi pada window 
	
	
	//wall
	mvwprintw(win, 0, 4, " [%s] ", namap); 				//output username
	mvwprintw(win, 19, 4, " Move [%i] ", point); 		//output banyaknya gerak
	mvwprintw(win, 19, 70, " [ Press ESC to exit ] "); 	//tekan tombol esc untuk exit saat sedang bermain
	
	
	wall(win); //output map atau peta
	
	
	wmove(win, y, x);		//awal mulai pergerakan
	wprintw(win, player); 	//output player
	wrefresh(win); 			//menyegarkan layar pada window
	
	keypad(win, TRUE); 		//supaya dapat dideteksi penekanan tombol khusus seperti F1 - F10, panah kanan, panah kiri dst...
	curs_set(0); 			//menyebunyikan tampilan kursor
	
	//pergerakan menggunakan tombol arrow atau panah pada keyboard
	while(true){
		int movement;
		bool move;
		movement = wgetch(win);

		switch(movement){
			case KEY_ESC:
				return 0;
				break;
				
			case KEY_LEFT:
				if(x == 1){
					x = 1; 		//batas kiri
				}else if(move){
					x = 95; 	//kolom finish
				}else{
					x--;
					point++; 	//menambah nilai movement
				}
				
				//====================================
				if(done(win) == 1){
					finish(win);
					wgetch(win);
					wclear(win);
					goto start; //mengarahkan pada start
				}
			 break;
			 
			case KEY_RIGHT:
				if(x == 96){
					x = 96;		//batas kanan
				}else if(move){
					x = 36;		//kolom game over
				}else{
					x++;
					point++;
				}
				
				//====================================
				if(end2(win) == 1){
					over(win);
					wgetch(win);
					wclear(win);
					goto start;
				}
				break;
				
			case KEY_UP:
				if(y == 1){
					y = 1;		//batas atas
				}else if(move){
					x = 38;		//kolom finish
				}else{
					y--;
					point++;
				}
				
				//====================================
				if(done2(win) == 1){
					finish(win);
					wgetch(win);
					wclear(win);
					goto start;
				}
				break;
				
			case KEY_DOWN:
				if(y == 18){
					y = 18;		//batas bawah
				}else if(move){
					y = 7;		//baris game over
					x = 2;		//kolom game over
				}else{
					y++;
					point++;
				}
			
				//====================================
				if(end(win) == 1){
					over(win);
					wgetch(win);
					wclear(win);
					goto start;
				}
				
		}
		
		wclear(win);
		box(win, 1, 1);
		
		
		//wall
		mvwprintw(win, 0, 4, " [%s] ", namap);
		mvwprintw(win, 19, 4, " Move [%i] ", point);
		wall(win);
	
		wmove(win, y, x);
		wprintw(win, player);
		wrefresh(win);
		
	}
		
	
	getch();
	endwin(); //fungsi untuk keluar dari ncurses
	
return 0;}
