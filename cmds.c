#include <stdio.h>
#include <strings.h>
#include <Windows.h>

#define S 64
#define M 124
#define L 256

void readcommands();
void readlinks();
void viewlists();
void addcommand(char *a);
void addlink(char *a);
void delcommand(char *a);

char commands[S][S];
char links[S][M];
char path[L];
char drive[MAX_PATH+1],dir  [MAX_PATH+1],fname[MAX_PATH+1],ext  [MAX_PATH+1];
char commandspath[L];
char linkspath[L];

int main(int argc, char *argv[])
{
    //pathの読み込み(read PATH)
    if(0!=GetModuleFileName( NULL, path, MAX_PATH )){// 実行ファイルの完全パスを取得
            _splitpath(path,drive,dir,fname,ext);//パス名を構成要素に分解します
    }
    sprintf(commandspath,"%s\\commands.txt",dir);
    sprintf(linkspath,"%s\\links.txt",dir);

    //command処理(get command)
    if(!strcmp(argv[1],"-add")){
        if(strlen(argv[3]) == 0){
            printf(" Error : Can't found link.\n");
            printf("    C:\\>open [-add] [sitecommand] [weblink]\n");
            printf("    ex: >open -add g https://www.google.com/search?q=");
            printf(" WORNIG : [weblink] is removed keyword from searching URL");
            return -2;
        }
        printf("Added : [ %s ] | [ %s ]\n",argv[2],argv[3]);
        addcommand(argv[2]);
        addlink(argv[3]);
        return 1;
    }
    readcommands(); //commands.txt読み込み(read commands.txt)
    readlinks(); //links.txt読み込み(read links.txt)
    if(!strcmp(argv[1],"-list")){
        viewlists();
        return 2;
    }
    if(!strcmp(argv[1],"-del")){
        printf("DELETE : [ %s ]\n",argv[2]);
        delcommand(argv[2]);
        return 3;
    }

    int i=0;
    char *site;
    //commnads.txtを参照(seach cmd to commands.txt)
    while(strlen(commands[i]) != 0){
        char cmd[S];
        sprintf(cmd,"%s\n",argv[1]);
        if(!strcmp(cmd,commands[i])){
            site = links[i];
            break;
        }
        i+=1;
    }
    //エラー表示(display 'Error')
    if(strlen(commands[i]) == 0){
        printf(" Error : No such thing as \"%s\" site\n",argv[1]);
        printf("By use command'open -list',You can view commands list.\n");
        printf("    C:\\>open [sitecommand] [word]\n");
        return -1;
    }
    
    //検索ワードの結合(join word)
    char word[M];
    sprintf(word, "%s",argv[2]);
    if(2 < argc){
        for (int i=3;i<argc;i+=1){
            strcat(word," ");
            strcat(word,argv[i]);
        }
    }

    //url作成(make URL)
    char url[L];
    sprintf(url, "%s%s", site, word);
    printf(" Open : %s  ",word);
 
    //url実行(open URL)
    ShellExecute(NULL,"open",url,NULL,NULL,SW_SHOWNORMAL);
    return 0;
}

//command.txt読み込み(read command.txt)
void readcommands(){
    int i=0;
    FILE *fp;
    char a[S];
    fp = fopen(commandspath,"r");
    while(fgets(a,S,fp) != NULL){
        sprintf(commands[i],"%s",a);
        i+=1;
    }
    fclose(fp);
}

//links.txt読み込み(read links.txt)
void readlinks(){
    int i=0;
    FILE *fp;
    char a[M];
    fp = fopen(linkspath,"r");
    while(fgets(a,S,fp) != NULL){
        sprintf(links[i],"%s",a);
        i+=1;
    }
    fclose(fp);
}

//-listされたときにコマンドを表示する(view filelists when '-list')
void viewlists(){
    int i=0;
    while(strlen(commands[i]) != 0){
        printf("%s|- %s\n",commands[i],links[i]);
        i+=1;
    }
}

//-addされたときにコマンドをファイルに追加(add command to commands.txt when '-add')
void addcommand(char *a){
    FILE *fp;
    fp = fopen(commandspath,"a");
    fprintf(fp,"%s\n",a);
    fclose(fp);
}

//-addされたときにリンクをファイルに追加(add link to links.txt when '-add')
void addlink(char *a){
    FILE *fp;
    fp = fopen(linkspath,"a");
    fprintf(fp,"%s\n",a);
    fclose(fp);
}

//-delされたときに対象コマンドを削除(deleate command when '-del')
void delcommand(char *a){

    int i=0,n;
    //commands.txtを参照(seach cmd to commands.txt)
    while(strlen(commands[i]) != 0){
        char cmd[S];
        sprintf(cmd,"%s\n",a);
        if(!strcmp(cmd,commands[i])){
            n=i;
            break;
        }
        i+=1;
    }
    //エラー表示(display 'Error')
    if(strlen(commands[i]) == 0){
        printf(" Error : No such thing as \"%s\"\n",a);
        printf("By use command'open -list',You can view commands list.\n");
        return;
    }
    i=0;
    FILE *fp1;
    FILE *fp2;
    fp1 = fopen(commandspath,"w");
    fp2 = fopen(linkspath,"w");
    //delしたファイルで作り直す   
    while(strlen(commands[i]) != 0){
        if(i == n)
            i+=1;
        fprintf(fp1,"%s",commands[i]);
        fprintf(fp2,"%s",links[i]);
        i+=1;
    }
    printf("    SUCCESS\n");
    fclose(fp1);
    fclose(fp2);
}