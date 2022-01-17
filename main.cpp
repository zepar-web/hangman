#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

int fr[200]={0};
void desenPlatou(){
    line(50, 400, 400, 400);
    line(175, 400, 175, 50);
    line(175, 50, 400, 50);
    line(0,610,900,610);
    outtextxy(10, 615,"Literele folosite:");
}
void liniuteCuvant(char cuvant[]){
    line(0,450, 800, 450);
    int x=50;
    for(int i=1;i<=strlen(cuvant)-1;i++){
        line(x*i+(i-1)*10,600,x*i+(i-1)*10+20,600);
    }
}
void liniuteCuvantDat(char cuvant[]){
    line(0,450, 800, 450);
    int x=50;
    for(int i=1;i<=strlen(cuvant);i++){
        line(x*i+(i-1)*10,600,x*i+(i-1)*10+20,600);
    }
}
void desenCap(){
    circle(400, 100, 35);
    line(400, 50, 400, 65);
}
void desenCorp(){
    line(400, 135, 400, 300);
}
void desenManaStanga(){
    line(400, 150, 350, 200);
}
void desenManaDreapta(){
    line(400, 150, 450, 200);
}
void desenPiciorDreapta(){
    line(400, 300, 450, 350);
}
void desenPiciorStanga(){
    line(400, 300, 350, 350);
}
void dead(){
    line(412, 85, 420, 95);
    line(420, 85, 412, 95);
    line(380, 85, 388, 95);
    line(388, 85, 380, 95);
    outtextxy(400, 10, "GAME OVER");
}
void desenGreseala(int greseala){
switch(greseala){
            case 1:
                desenCap();
                break;
            case 2:
                desenCorp();
                break;
            case 3:
                desenManaStanga();
                break;
            case 4:
                desenManaDreapta();
                break;
            case 5:
                desenPiciorDreapta();
                break;
            case 6:
                desenPiciorStanga();
                break;
            case 7:
                dead();
                break;
        }
}
void alegereDomeniu(int alegere, char cuvant[50]){
    srand(time(0));
    if(alegere==1){
        FILE *fptr;
            if ((fptr = fopen("animale.txt","r")) == NULL)
            {
                perror("Erroare la deschiderea fisierului");
                exit(1);
            }
            char linie[200];
            int check=0;
            int random = 0;
            random = rand()%16;
            while(fgets(linie,200,fptr))
            {
                if (check==random){
                    printf("%s\n",linie);
                    strcpy(cuvant, linie);
                }
                check++;
            }
            fclose(fptr);
    }else if(alegere==2){
     FILE *fptr;
            if ((fptr = fopen("orase.txt","r")) == NULL)
            {
                perror("Erroare la deschiderea fisierului");
                exit(1);
            }
            char linie[200];
            int check=0;
            int random = 0;
            random = rand()%15;
            while(fgets(linie,200,fptr))
            {
                if (check==random){
                    printf("%s\n",linie);
                    strcpy(cuvant, linie);
                }
                check++;
            }
            fclose(fptr);
    }else if(alegere==3){
        cout<<"Scrie cuvantul:"<<endl;
        cin.get();
        cin.get(cuvant, 50);
        cin.get();
    }
    int i;
    for(i=0;i<strlen(cuvant);i++){
        fr[cuvant[i]]++;
    }
}
int main()
{
    char cuvant[50], guess, copieV[50], copieG[50], verificareGreseala[50]="";
    int alegere, greseala =0, corect=0, xCG=120;
    bool running = true;
    cout<<"Alege domeniul:"<<endl;
    cout<<"1) Animale "<<endl;
    cout<<"2) Orase "<<endl;
    cout<<"3) Introduceti cuvantul "<<endl;
    cin>>alegere;
    alegereDomeniu(alegere,cuvant);
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    initwindow(800, 800,"Hangman");
    while(running){
        desenPlatou();
        if(alegere==1 || alegere==2){
            liniuteCuvant(cuvant);
        }else if(alegere==3){
            liniuteCuvantDat(cuvant);
        }
        cin>>guess;
        copieG[0]=guess;
        copieG[1]='\0';
        outtextxy(xCG,615, copieG);
        xCG+=10;
        bool gasit=false;
            for(int i=0;i<strlen(cuvant);i++){
                if(cuvant[i]==guess && fr[cuvant[i]]!=0){
                    gasit=true;
                    copieV[0]=cuvant[i];
                    copieV[1]='\0';
                    int x=50;
                    outtextxy(x*i+(i-1)*10+65,575, copieV);
                    corect +=1;
                    //PlaySound("tada.wav", NULL, SND_ASYNC);
                    fr[cuvant[i]]--;
                }
            }
        if(gasit==false){
            greseala +=1;
            //PlaySound("buzz.wav", NULL, SND_ASYNC);
        }
        if(greseala==7) running=false;
        if(corect>=strlen(cuvant)-1 && (alegere==1 || alegere==2)){
            outtextxy(400, 10, "You WON!");
            running=false;
        }else if(corect==strlen(cuvant)){
            outtextxy(400, 10, "You WON!");
            running=false;
        }
        desenGreseala(greseala);
    }
    getch();
    closegraph();
 return 0;
}
