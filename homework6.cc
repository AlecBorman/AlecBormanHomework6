/*
 * Usage of homework6,cc
 *
 * 
 * Author: Alec Borman
 * Email:  amb161530@utdallas.edu
 */
#include <sstream>
#include <iostream>
#include "cdk.h"
#include "BinaryFileHeader.h"
#include <cstdint>
#include <sys/types.h>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <fstream>
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 16
#define MATRIX_NAME_STRING "BinaryFileDisplay"

using namespace std;


int main()
{
  //before all of this I need to pull my actual data from the binary file
  //BinaryFileHeader *BinaryFile = new BinaryFileHeader();
  //ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  //binInfile.read((char *) BinaryFile, sizeof(BinaryFileHeader));
  //stringstream ss;
  //char* matrix11;
  //ss << matrix11;
  //s/s >> BinaryFile->magicNumber;
  
  //char* matrix12 = (int)y(BinaryFile -> versionNumber);
  //char* matrix13 = (int)(BinaryFile -> numRecords); 
  //const char* matrix11 = temp.c_str();
  //char* matrix11 = temp.c_str();
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  //drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */

  //before all of this I need to pull my actual data from the binary file
  BinaryFileHeader *BinaryFile = new BinaryFileHeader();
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  binInfile.read((char *) BinaryFile, sizeof(BinaryFileHeader));
  
  //Get a char* to hold the string. setCDKmatrixcell requires a char*
  char* magicNumber = new char[BOX_WIDTH]; //We know the box length already, so we can use a fixed-length array
  char* versionNumber = new char[BOX_WIDTH];
  char* numRecords = new char[BOX_WIDTH];

  sprintf(magicNumber, "Magic: %02X", BinaryFile->magicNumber);
  sprintf(versionNumber, "Verstion: %u", BinaryFile->versionNumber);
  sprintf(numRecords, "NumRecords: %u", (unsigned)BinaryFile->numRecords);
  setCDKMatrixCell(myMatrix, 1, 1, magicNumber);
  setCDKMatrixCell(myMatrix, 1, 2, versionNumber);
  setCDKMatrixCell(myMatrix, 1, 3, numRecords);
  //setCDKMatrixCell(myMatrix, 1, 2, matrix12);
  //setCDKMatrixCell(myMatrix, 1, 3, matrix13);


  BinaryFileRecord *BinaryFileR = new BinaryFileRecord();
  binInfile.read((char *) BinaryFileR, sizeof(BinaryFileRecord));
  char* strLength = new char[BOX_WIDTH];
  char* stringBuffer = new char[BOX_WIDTH];
  sprintf(strLength, "Strlen: %i",(int)strlen(BinaryFileR -> stringBuffer));
  sprintf(stringBuffer, "%s", BinaryFileR -> stringBuffer);
  setCDKMatrixCell(myMatrix, 2, 1, strLength);  
  setCDKMatrixCell(myMatrix, 2, 2, stringBuffer);
  
  BinaryFileR = new BinaryFileRecord();
  binInfile.read((char *) BinaryFileR, sizeof(BinaryFileRecord));
  strLength = new char[BOX_WIDTH];
  stringBuffer = new char[BOX_WIDTH];
  sprintf(strLength, "Strlen: %i",(int)strlen(BinaryFileR -> stringBuffer));
  sprintf(stringBuffer, "%s", BinaryFileR -> stringBuffer);
  setCDKMatrixCell(myMatrix, 3, 1, strLength);
  setCDKMatrixCell(myMatrix, 3, 2, stringBuffer);


  BinaryFileR = new BinaryFileRecord();
  binInfile.read((char *) BinaryFileR, sizeof(BinaryFileRecord));
  strLength = new char[BOX_WIDTH];
  stringBuffer = new char[BOX_WIDTH];
  sprintf(strLength, "Strlen: %i",(int)strlen(BinaryFileR -> stringBuffer));
  sprintf(stringBuffer, "%s", BinaryFileR -> stringBuffer);
  setCDKMatrixCell(myMatrix, 4, 1, strLength);
  setCDKMatrixCell(myMatrix, 4, 2, stringBuffer);

  BinaryFileR = new BinaryFileRecord();
  binInfile.read((char *) BinaryFileR, sizeof(BinaryFileRecord));
  strLength = new char[BOX_WIDTH];
  stringBuffer = new char[BOX_WIDTH];
  sprintf(strLength, "Strlen: %i",(int)strlen(BinaryFileR -> stringBuffer));
  sprintf(stringBuffer, "%s", BinaryFileR -> stringBuffer);
  setCDKMatrixCell(myMatrix, 5, 1, strLength);
  setCDKMatrixCell(myMatrix, 5, 2, stringBuffer);



                                                                
  drawCDKMatrix(myMatrix, true);    /* required  */ 


  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
