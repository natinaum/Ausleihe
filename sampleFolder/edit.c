#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#define MAX_CMD_LEN 10
#define GET       0
#define SET       1
#define ADD       2
#define LINK      3
#define ADDPERSON 4
#define LNADD     5
#define ARGS_N 6

char Args[ARGS_N][MAX_CMD_LEN]={"get","set","add","link","addperson","lnadd"};






void help(){
	printf("\
	edit get <path> <bezeichner> //prints value from json file\n \
	edit set <path> <bezeichner> <value> //sets value of json file\n \n \
	edit add <path> <bezeichner> <type(vorlage)>  //typ: Objekt/Person\n \
	edit link <path> <path> //links json file from objekt/person/ort folder (path --simlink--> path)\n \n \
	complex functions:\n \
	edit addPerson <Name>\n \
	edit lnadd <path> <type> <person/ort> //links object to person or place\n \
	\n"); 
}

int FunctionNameToID(char * function){
	int i=ARGS_N;
	while(i){
		i--;
		if(!strcmp(Args[i],function)) return i;
	}
	return -1;
}

_Bool isJSONENTR(char * line){
	for(int i =0;i<strlen(line);i++){
		if(line[i]==':'){
			for(;i<strlen(line);i++){
				if(line[i]=='"'){
					for(;i<strlen(line);i++){
						if(line[i]=='"'){
							for(;i<strlen(line);i++){
								if(line[i]==';'){
									return 1;
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}


int GetObj(char *line,char ** obj){
	// kopiert Inhalt einer JSON Zeile - mit Feldern - in obj char** (0 Bezeichner, 1 Inhalt)
	char * Bezeichner=obj[0];
	char * Value=obj[1];
	if(isJSONENTR(line)){
		int i,j;
		for(i=0;line[i]<33;i++);
		for(j=0; line[i+j]!=58;j++){
			Bezeichner[j]=line[j+i];
		}
		Bezeichner[j]=0;
		for(i=i+j;line[i]!='"';i++);
		i++;
		for(j=0; line[i+j]!='"';j++){
			Value[j]=line[j+i];
		}
		Value[j]=0;

		return 0;
	}else{
		return 1;
	}
}



void get(char * path, char * feldname){ //Gibt Inhalt eines angegebenen Feldes zurück
	printf("Hole aus %s folgendes Feld: %s \n", path, feldname);
	char ** obj=malloc(2);
	obj[0]=malloc(50);
	obj[1]=malloc(50);
	FILE * fp;
	fp=fopen(path, "r");

	char *line = NULL;
	size_t len = 0;
	while(getline(&line, &len, fp) != -1) {
		 if(!GetObj(line, obj)&&!strcmp(obj[0],feldname))
		 printf("%s\n",obj[1]);
	}
	free (obj[0]);
	free (obj[1]);
	free (obj);
	free (line);
	fclose(fp);
}
void set(char * path, char * feldname, char *newValue){
	char ** obj=malloc(2);
	obj[0]=malloc(50);
	obj[1]=malloc(50);
	FILE * fp;
	printf("test\n");
	fp=fopen(path, "rw");
	FILE* tmp;
	char  TEMPLATE[]="./FXXXXXX";
	int fd=mkstemp(TEMPLATE);
	tmp=fdopen(fd,"w");

	char *line = NULL;
	size_t len = 0;
	while(getline(&line, &len, fp) != -1) {
		 if(!GetObj(line, obj)&&!strcmp(obj[0],feldname)){
		 	fputs("    ",tmp);
		 	fputs(obj[0],tmp);
		 	fputs(": \"",tmp);
		 	fputs(newValue,tmp);
		 	fputs("\";\n",tmp);
		 }else{
		 	fputs(line,tmp);
		 }
	}
	free (obj[0]);
	free (obj[1]);
	free (obj);
	free (line);
	fclose(fp);
	fclose(tmp);
	rename(TEMPLATE, path);
}


int main(int argN,char ** args){
	int FunctionID=-1;
	if(argN>1){
		char * function = malloc(MAX_CMD_LEN);
		strcpy(function, args[1]);
		FunctionID=FunctionNameToID(function);
	}
	switch(FunctionID){
		case GET:
			if(argN>3)
				get(args[2],args[3]);
				else help();
			break;
				
		case SET:
			if(argN>4)
				set(args[2],args[3],args[4]);
			else help();
			break;
		case ADD:
			printf("GET\n");
			break;
		case LINK:
			printf("LINK\n");
			break;
		case ADDPERSON:
			printf("ADDPERSON\n");
			break;
		case LNADD:
			printf("LNADD\n");
			break;
		default:
			help();
	}

}


