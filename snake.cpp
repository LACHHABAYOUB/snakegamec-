
#include <conio.h>
#include <stdio.h>
#include <time.h>

   int i, j;
   int ox, oy;         //  origine tableau
   int x, y, avx, avy;
   int lignes, colonnes;
   char c;
   int sens, vitesse;
   int snake, avsnake, greffe=5;
   int poxal, poyal, pomme=0;      //  pomme
   int posx[201];
   int posy[201];
   int c_fond=62, c_bordure=49 , c_pomme=44, c_normal=15, c_snake=2;  //  couleurs
   int niveau=1;
   int gagne=0;
   char recommencer;

   void reglages();
   void tableau();
   void initsnake();
   void collision();
   void test_clavier();
   void affichage_snake();
   void test_position();
   void creer_pomme();
   void test_pomme();
   void gagner();
   void perdu();
   void eff_ecran();

void main(){

   if(gagne!=1) reglages();
   srand(time(NULL));
   tableau();
   creer_pomme();
   initsnake();
   do{
      collision();
      test_pomme();
      test_position();
      affichage_snake();
      test_clavier();

   }while((c!=27) && (x!=ox+(colonnes)) && (x!=ox-1) && (y!=oy+(lignes)) && (y!=oy-1));
   perdu();
}

void reglages(){
   clrscr();
   textcolor(c_normal);
   gotoxy(30,2);printf("---------");
   gotoxy(30,3);printf("| SNAKE |");
   gotoxy(30,4);printf("---------");
   gotoxy(1,9);
   do{
      printf(" lignes (entre 10 et 15) : ");
      scanf("%d",&lignes);                      //  saisie du nombre de lignes
      if((lignes<10) || (lignes>15)) ;
   }while((lignes<10) || (lignes>15));
   do{
      printf("\n colonnes (entre 10 et 60) : ");
      scanf("%d",&colonnes);                    //  saisie du nombre de colonnes
      if((colonnes<10) || (colonnes>60)) ;
   }while((colonnes<10) || (colonnes>60));
   do{
      printf("\n niveau (entre 1 et 6) : ");
      scanf("%d",&niveau);                      //  saisie du niveau
      if((niveau<1) || (niveau>6)) ;
   }while((niveau<1) || (niveau>6));
   do{
      gotoxy(26,19);
      printf(" appuyer sur une touche");
      Sleep(650);
      gotoxy(26,19);
      printf("                       ");
      Sleep(650);
   }while(kbhit()==0);
   clrscr();
}

void tableau(){
    ox=39-(colonnes/2);
    oy=14-(lignes/2);
    textcolor(c_normal);
    gotoxy(30,2);printf("---------");
    gotoxy(30,3);printf("| SNAKE |");
    gotoxy(30,4);printf("---------");
    textcolor(c_fond);
    for(i=0;i<=colonnes+1;i++){
      for(j=0;j<=lignes+1;j++){
         gotoxy((ox-1)+i,(oy-1)+j);
         if((ox+i==ox)||(ox+i-1==(ox+colonnes))||(oy+j==oy)||(oy+j-1==(lignes+oy))){textcolor(c_bordure); printf("%c",178);}
         else printf("%c",177);
         textcolor(c_fond);
      }
   }
}

void initsnake(){
   x=35;
   y=14;
   snake=5;
   for(i=0;i<=201;i++){
      posx[i]=0;
      posy[i]=0;
   }
   for(i=snake;i>0;i--,x++){
      posx[i]=x;
      posy[i]=y;
   }
   x--;
   avx=x; avy=y;
   sens=1;          //  sens vers la droite par default
   j=0;
}

void collision(){
   for(i=2;i<=snake;i++){
      if((posx[1]==posx[i])&&(posy[1]==posy[i])) perdu();
   }
}

void creer_pomme(){
   textcolor(c_pomme);
   poxal= ( rand()% colonnes )+ ox ;                           // position de la pomme sur l'axe x
   poyal= ( rand()% lignes)+ oy  ;                             // position de la pomme sur l'axe y
   for(i=1;i<=snake;i++){                                      // test si la position du serpent
      if((poxal==posx[i])&&(poyal==posy[i])) creer_pomme();    // est confondue avec la position
   }                                                           // de la pomme
   gotoxy(poxal,poyal); printf("%c",770);
   if(gagne==1)getch();                       // créer une pause si on passe un niveau
}

void test_pomme(){
    if((posx[1]==poxal)&&(posy[1]==poyal)){   //  test si les coordonnées de la pomme sont
       pomme++;                               //  égales à celles du serpent
       gagner();
       snake+=greffe;
       creer_pomme();
    }
}

void affichage_snake(){
   for(i=snake;i>=0;i--){
      gotoxy(posx[i],posy[i]);
      if(i==0){
         textcolor(c_fond);
         printf("%c",177);
      }else textcolor(c_snake);
         if(i==1)           printf("%c",178);
         if((i!=0)&&(i!=1)) printf("%c",219);
   }
   textcolor (c_normal);
   gotoxy(ox-1,oy+lignes+2);
   printf("niveau: %2.d",niveau);                                   // affichage du niveau
   gotoxy(ox-1,oy+lignes+2+1);
   printf("pomme(s) :%2.d/%2.d",pomme,(((lignes*colonnes)/30)+6));  // affichage nbre de pommme
   textcolor (c_fond);
}

void test_position(){
   if((avx!=x)||(avy!=y)){
      if(snake==avsnake){         //  longueur de snake inchangée

         posx[0]=posx[snake];
         posy[0]=posy[snake];
         for(i=snake;i>1;i--){
            posx[i]=posx[i-1];
            posy[i]=posy[i-1];
         }
      }
      if(snake!=avsnake){         //  longueur de snake changée

         posx[0]=posx[avsnake];
         posy[0]=posy[avsnake];
         for(i=avsnake;i>1;i--){
            posx[i]=posx[i-1];
            posy[i]=posy[i-1];
         }
         for(i=(avsnake+1);i<=snake;i++){
            posx[i]=posx[i-1];
            posy[i]=posy[i-1];
         }
      }
      if(avx!=x) posx[1]=x;       //   test si la tete du serpent a changé soit sur l'axe x
      if(avy!=y) posy[1]=y;       //   ou sur l'axe y
   }
   avsnake=snake;   //  longueur du serpent en mémoire
   avx=x; avy=y;    //  coordonnées de la tete en memoire
}

void test_clavier(){
   if(kbhit()==1){                           //  si une touche est frappée
      c=getch();
      switch(c){
         case 'd' : if(sens!=3){
                       x++ ;
                       sens=1;
                       }else x-- ; break;
         case 'q' : if(sens!=1){
                       x-- ;
                       sens=3;
                       }else x++ ; break;
         case 's' : if(sens!=2){
                       y++ ;
                       sens=4;
                       }else y-- ; break;
         case 'z' : if(sens!=4){
                       y-- ;
                       sens=2;
                       }else y++ ; break;
         case 'p' : getch() ; break;
      }
   }
   else{                                     //  aucune touche frappée
      switch(sens){
         case 1 : x++; break;
         case 3 : x--; break;
         case 4 : y++; break;
         case 2 : y--; break;
      }
   }
   switch(niveau){                           // change la vitesse en fonction du niveau
         case 1: vitesse=120  ; break ;
         case 2: vitesse=90   ; break ;
         case 3: vitesse=65   ; break ;
         case 4: vitesse=40   ; break ;
         case 5: vitesse=20   ; break ;
         case 6: vitesse=15   ; break ;
      }
   Sleep(vitesse);
}

void gagner(){
   if(pomme==(((lignes*colonnes)/30)+6)){
      pomme=0;
      eff_ecran();
      niveau++;
      if(niveau>7){                          // jeu terminé
         gagne=0;
         gotoxy(30,7);
         textcolor(c_normal);
         printf(" Gagne ");
         Sleep(700);
         getch();
         main();
      }
      gagne=1;
      main();
   }
}

void perdu(){
  do{
      pomme=0;
      if(kbhit()==1) exit(1);
      i++;
      textcolor(c_normal);
      gotoxy(32,3);
      printf("PERDU");
      Sleep(700);
      gotoxy(32,3);
      printf("     ");
      Sleep(700);
   }while(kbhit()==0);
   getch();
   Sleep(60);
   textcolor(c_normal);
   gotoxy(30,2);
   printf("         ");
   gotoxy(30,4);
   printf("         ");
   gotoxy(26,3);
   printf("recommencer? (o/n)");
   do{
      recommencer=getch();
      if((recommencer=='o')||(recommencer=='O')){
         lignes=0;
         colonnes=0;
         eff_ecran();
         main();
      }
      if((recommencer=='n')||(recommencer=='N')) exit(1);
   }while((recommencer!='o')||(recommencer!='O')||(recommencer!='n')||(recommencer!='N'));
}

void eff_ecran(){
   textcolor(0);
   for(i=0;i<=70;i++){
      for(j=0;j<=23;j++){
         gotoxy(i,j);
         printf("%c",177);
      }
   }
}
