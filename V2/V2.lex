%{
/* Fichier exAtt.lex */
#include "yystype.h"
#include "yygrammar.h"

char err[20]; /* Chaine de caracteres pour les erreurs de syntaxe */
%}

/* Definition de macros */
chiffre         [0-9]
separateur      [ \t]
lettre    		[a-zA-Z]    		
id   			[a-zA-Z0-9]|-|_

%%




"<?xml" 										   		return ENTETE;    /* Indique au parser que l'entête est reconnu */
"version"												return ATT_VERSION; /* Indique au parser qu'un attribut version est reconnu */ 
"\"1.0\""												return VALEUR_VERSION; /* Indique au parser la version de l'attribut version est reconnu */ 
"encoding" 												return ATT_ENCODING; /* Indique au parser qu'un attribut encoding est reconnu */ 
"\"UTF-8\""												return ATT_UTF; /* Indique au parser le type d'encodage de l'attribut encoding est reconnu */ 


"<scxml"												return oBALISE_SCXML; /* Indique au parser qu'une balise ouvrante  scxml  est reconnu  */
"xmlns" 												return ATT_XMLNS; /* Indique au parser qu'un attribut xmlns est reconnu */ 
"\"http://www.w3.org/2005/07/scxml\""					return VALEUR_REF; /* Indique au parser que la référence de l'attribut xmlns est reconnu */ 
"initial"												return ATT_INIT; /* Indique au parser qu'un attribut initial est reconnu */ 
"</scxml"												return fBALISE_SCXML; /* Indique au parser qu'une balise fermante  scxml   est reconnu  */ 

"<state"												return oBALISE_STATE; /* Indique au parser qu'une balise ouvrante  state   est reconnu  */
"id" 													return ATT_ID; /* Indique au parser qu'un attribut id est reconnu */ 
"final"													return ATT_FINAL; /* Indique au parser qu'un attribut final est reconnu */ 
"</state"												return fBALISE_STATE; /* Indique au parser qu'une balise fermante  state   est reconnu */ 

"<transition"											return oBALISE_TRANSITION ;   /* Indique au parser qu'une balise ouvrante transition est reconnu */
"event"													return ATT_EVENT;    /* Indique au parser que l'attribut event est reconnu */
"target"												return ATT_TARGET;    /* Indique au parser que l'attribut target est reconnu */

"\"true\""												return TRUE;  /* Indique au parser qu un boolean TRUE est reconnu */
"\"false\""												return FALSE;  /* Indique au parser qu un boolean  FALSE est reconnu */
\"{lettre}{id}*\"										{ yylval.id = (char * ) malloc (strlen(yytext)*sizeof(char)+1 ) ; strcpy(yylval.id , yytext + 1 ) ;yylval.id[strlen(yytext)-2] = '\0' ;   return IDENTIFIANT; }    /* Indique au parser qu un identifiant  est reconnu */


"?>"													return fENTETE; /* Indique au parser qu'une balise fermante  xml est reconnu */ 
"/>"													return fBALISE_TRANSITION; /* Indique au parser qu'une balise fermante transition est reconnu */
">"														return BALISEf; /* Indique au parser qu'une fin de balise simple  est reconnu   (>)*/ 	
"="														return EGALE; /* Indique au parser qu'un signe égale  est reconnu */ 	

{separateur}+       									;                  /* Elimination des espaces */
\n                  									yypos++;           /* Compte le nombre de lignes du fichier source */
.                   									{ sprintf(err,"Mauvais caractere %c",yytext[0]);
                    									  yyerror(err);    /* Generation d'une erreur de syntaxe */
                    									}
%%
