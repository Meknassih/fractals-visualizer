#include <stdio.h>
#include <stdlib.h>
#include "listep.h"
#include "listep_op.h"

/*
 * Fichier test des listes.
 * A completer pour autres operations.
 */

int testLectureEcriture() {
	PLISTE pl = lire_liste("liste.in");
	ecrire_liste("liste.out", pl);
	return 0;
}
	

int main() {
  return testLectureEcriture();
}
