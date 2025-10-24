#include "mini_lib.h"
#include <unistd.h>
#define max 20
#define DEBUG
#include <stdio.h>

void showMem(){
   extern struct malloc_element* malloc_list;
   struct malloc_element* element = malloc_list;
   while (element != NULL){
      #ifdef DEBUG
         printf("--- Malloc Info --- \n");
         printf("addr = %p \n", element->addr);
         printf("size %zu\n", element->size);
         printf("status %i\n", element->status);
         printf("next_addr %p\n", element->next_malloc);
      #endif
         element = element->next_malloc;
   }
}

int main(int argc, char *argv[]) {
   void* addr;
   void* addr2;
   // code linked to questions 8 to 11
   extern struct malloc_element* malloc_list;
   if ((addr = mini_calloc(sizeof(int), 2))){
      //write(1, "Created pointer successfully \n", 30);

   }
   if ((addr2 = mini_calloc(sizeof(int), 2))){
      //write(1, "Created pointer successfully \n", 30);

   }
   //mini_free(addr);
   showMem();
   #ifdef DEBUG
   printf("SHOW MEM DEUXIEME PARTIE \n");
   #endif
   mini_calloc(sizeof(int), 2);

   if (0){
      write(1, "QUIT\n", 6);
      mini_exit();
   }

   showMem();
   //mini_printf("Voici une chaine de caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue, wawaywawyawaywyyayywawyaywaywyaywyawyawyaywyawyaywyaywyawyaywayawaywyaywaywaywawyaywyywayywawywywwywwyywyaaade caractère extrêmement longue,FIN DE LA CHAINE !");
   //mini_printf("Voici ma chaine de caractère !!!! \n noiuvelzjofsjeiofjziufjzeofjoz \n i");
   //mini_printf("Voici ma nouvelle chaine de caractère !!!! \n isqjdfqdsjfklsqdjf i\n");
   //mini_printf("Nouvelle chaine de caractèred");
   char test[5];
   int result = mini_scanf(test, 5);
   #ifdef DEBUG
   printf("Voic ma chaine de caractère, %s", test);
   #endif

   char* charar = "BONJOUR TOUT LE MONDE";
   char* dest = mini_calloc(sizeof(char),mini_strlen(charar, 4096));
   int testSize = mini_strlen(charar, 4096);
   #ifdef DEBUG
   printf("STr size %i  \n", testSize);
   #endif
   int charCopied = mini_strcpy(charar, dest, testSize);
   dest = "WIWOUWOUWOU";
   int cmp = mini_strcmp(charar, dest, testSize);
   #ifdef DEBUG
   printf("Copied %i \n", charCopied);
   printf("Cmp result %i\n", cmp);


   int* nvValue = mini_calloc(sizeof(int), 1);
   *nvValue = 500;
   
   
   printf("valeur de nvalue : %i \n", *nvValue);
   #endif
   char* fileBuff = mini_calloc(sizeof(char),1);
   MYFILE* monNvFile = mini_fopen("res.txt", 'r');
   MYFILE* monFile = mini_fopen("file.txt", 'r');
   if (monFile == NULL){
      mini_perror("Erreur d'ouverture du fichier");
   }
   
   int readBytes = mini_fread(fileBuff, sizeof(char),1, monFile);
   #ifdef DEBUG
   printf("Lu %i octets \n", readBytes);
   printf("READ %s \n", fileBuff);
   #endif
   MYFILE* monFileToW = mini_fopen("wFile.txt", 'w');
   if (monFileToW == NULL){
      mini_perror("Erreur d'ouverture du fichier");
   }
   char* reallyLongChar = "jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzhjsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzhjsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh-jsqjfqdkljfioajiojfiuatjreghiuzhaeuihfazeuifhsqiufhuziaerhuiargeziauhuzehriuzeahfuizaeghuiazhruizeahruzaiuizahfuziahriuzearhiuzaeghauzh";
   int writtenBytes = mini_fwrite(reallyLongChar, sizeof(char), 1080, monFileToW);
   mini_fputc(monFileToW, 'C');
   char caracter = mini_fgetc(monNvFile);
   
   mini_exit();
}