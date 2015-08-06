# xml_parsing_example
Quick demo of the expat library for parsing a simple XML document.

Based on: http://www.xml.com/pub/a/1999/09/expat/?page=2

Modified to show usage of a text handler.  The text handler is set/unset accordingly.


#### To compile

gcc -I<path_to_expat>expat/xmlparse outline.c -lexpat

Tested using Expat library version:

Headers sourced from: http://expat.cvs.sourceforge.net/viewvc/expat/expat/?view=tar&pathrev=V1_0

Linked against version: libexpat.so.1 libexpat.so.1.6.0


#### To run

$ ./a.out < xml
