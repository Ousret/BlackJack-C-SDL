/*
	Module: Tests Cunit pour bj_engine.c
	Auteur(s): TAHRI Ahmed, SIMON Jérémy, DEZERE Floriant, PROVOST Valentin
	Version: 1.0
	Date: 20/11/2014
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "CUnit/Basic.h"
#include "includes/bj_engine.h"

/* On inclus les tests sur la mise */
void testMise(void)
{
	CU_ASSERT_EQUAL( BJ_setBet(1, 100), 1);
	CU_ASSERT_EQUAL( BJ_setBet(1, 3), 0);
	CU_ASSERT_EQUAL( BJ_setBet(1, 900), -1);
}

/* On inclus les tests sur la modification de la solde */
void testAjoutSolde(void)
{
	CU_ASSERT_EQUAL( BJ_getScore(1), 0);
	CU_ASSERT_EQUAL( BJ_getScore(55), -1);
}

/* On test l'initialisation du jeu */
void testInitialisationJeu(void)
{
	CU_ASSERT_EQUAL( BJ_setGameProperties(10, 900, 0), 0);
}
/* On test la fonction aléatoire (int) */
void testRand(void) {

	int i = 0;
	
	for (i = 0; i < 10; i++) {
		CU_ASSERT(Random(0,3) <= 2);
		CU_ASSERT(Random(0,3) >= 0);
	}
	
}

int main()
{
	CU_pSuite pSuite = NULL;
	joueurs[1].solde = 780; //On initialise la solde du joueur pour effectuer des tests
	srand(time(NULL)); //On initialise le rand sur l'horloge sys (ms)
	
	/* Initialisation CUnit (Registre) */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* On prépare CUnit à lancer des tests */
	pSuite = CU_add_suite("Tests sur le moteur BlackJack", NULL, NULL);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* On prépare les tests */
	if ((NULL == CU_add_test(pSuite, "Test d'initialisation du jeu", testInitialisationJeu)) ||
		(NULL == CU_add_test(pSuite, "Tests sur la recup du score", testAjoutSolde)) ||
		(NULL == CU_add_test(pSuite, "Tests sur les mises", testMise)) ||
		(NULL == CU_add_test(pSuite, "Tests fonction rand()", testRand))) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
   
	return CU_get_error();
}
