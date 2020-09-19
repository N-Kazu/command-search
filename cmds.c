#include <stdio.h>
#include <strings.h>
#include <Windows.h>

char *google = "https://www.google.com/search?q=";
char *youtube = "https://www.youtube.com/results?search_query=";
char *wiki = "https://ja.wikipedia.org/wiki/";
char *opgg = "https://jp.op.gg/summoner/userName=";
char *opggc = "https://jp.op.gg/champion/";
char *speedrun = "https://www.speedrun.com/";

//^^
char *pornhub = "https://jp.pornhub.com/video/search?search=";

int main(int argc, char *argv[])
{
    char *site;
    if(!strcmp(argv[1],"google")){
        site = google;
    }
    if(!strcmp(argv[1],"g")){
        site = google;
    }
   else if(!strcmp(argv[1],"youtube")){
        site = youtube;
    }
    else if(!strcmp(argv[1],"wiki")){
        site = wiki;
    }
    else if(!strcmp(argv[1],"opgg")){
        site = opgg;
    }
    else if(!strcmp(argv[1],"opggc")){
        site = opggc;
    }
    else if(!strcmp(argv[1],"speedrun")){
        site = speedrun;
    }
    //^^
    else if(!strcmp(argv[1],"pornhub")){
        site = pornhub;
    }
    else{
        printf(" Error : No such thing as \"%s\" site\n",argv[1]);
        printf("    C:\\>open (site) (word)\n");
        return -1;
    }
    
    //char *word = argv[2];
    char word[100];
    sprintf(word, "%s",argv[2]);
    if(2 < argc){
        for (int i=3;i<argc;i+=1){
            strcat(word," ");
            strcat(word,argv[i]);
        }
    }

    char url[200];
 
    sprintf(url, "%s%s", site, word);
    printf(" Open : %s  ",word);
 
    ShellExecute(NULL,"open",url,NULL,NULL,SW_SHOWNORMAL);
    return 0;
}