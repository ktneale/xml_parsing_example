/*****************************************************************
 * outline.c
 *
 * Copyright 1999, Clark Cooper
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the same terms as Perl.
 *
 * Read an XML document from standard input and print an element
 * outline on standard output.
 *
 * Mod - Kevin Neale - 06/08/2015
 * Modified to demonstrate the use of a character handler.
 * Only text elements for the required elements are printed to stdout.
 * The handler is unset, when the required element is closed.
 */

#include <stdlib.h>
#include <stdio.h>
#include "xmlparse.h"

#define BUFFSIZE	8192

char Buff[BUFFSIZE];

//Global parser object
XML_Parser p;

int Depth;

void charhndl(void *data,const char *s,int len) {
    char temp[1024] = {'\0'};   //fixed size buffer limits length
    snprintf(temp,len+1,"%s",s);
    int i = 0;

    //Pretty print
    for(i=0;i<Depth-1;i++)
        printf("  ");

    printf("Text(%s)\n", temp);
}

void start(void *data, const char *el, const char **attr) {

  int i = 0, j = 0;

  for(j=0;j<Depth;j++)
    printf("  ");

  printf("ElementOpen(%s)\n", el);

  if(strcmp(el,"book")==0) XML_SetCharacterDataHandler(p,charhndl);

  for (i = 0; attr[i]; i += 2) {

  for(j=0;j<Depth;j++)
    printf("  ");

    printf("Attribute: Name(%s)=Value(%s)\n", attr[i], attr[i + 1]);
  }

  Depth++;
}  /* End of start handler */

void end(void *data, const char *el) {

  int i =0;

  if(strcmp(el,"book")==0) XML_SetCharacterDataHandler(p,NULL);

  for(i=0;i<Depth-1;i++)
    printf("  ");

  printf("ElementClose(%s)\n", el);

  Depth--;
}  /* End of end handler */

void main(int argc, char **argv) {

  p = XML_ParserCreate(NULL);

  if (! p) {
    fprintf(stderr, "Couldn't allocate memory for parser\n");
    exit(-1);
  }

  XML_SetElementHandler(p, start, end);

  for (;;) {
    int done;
    int len;

    len = fread(Buff, 1, BUFFSIZE, stdin);
    if (ferror(stdin)) {
      fprintf(stderr, "Read error\n");
      exit(-1);
    }
    done = feof(stdin);

    if (! XML_Parse(p, Buff, len, done)) {
      fprintf(stderr, "Parse error at line %d:\n%s\n",
	      XML_GetCurrentLineNumber(p),
	      XML_ErrorString(XML_GetErrorCode(p)));
      exit(-1);
    }

    if (done)
      break;
  }
}  /* End of main */

