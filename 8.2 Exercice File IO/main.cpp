#include <iostream>
#include <math.h>
#include <stdlib.h> 
#include <time.h>
#include <vector>

/*EXERCICE 8.2
 Rendu Git
En reprenant l’exercice 4.4 (Dragon VS Cochon), le programme doit être capable de lire/construire les cochons et le dragon.
Cela peut être fait avec un ou plusieurs fichier, mais il faut utiliser un format JSON.*/

///////////////////////////////////////////////////////////////////////////////////////////////

/*Créer un programme qui va simuler un combat entre un dragon et 10 cochons (Les cochons sont dans la même équipe et s’attaquent uniquement au dragon).
Cela implique que chaque créature commence avec un certain nombre de points de vie (dragon : 100, cochons : 10).
Ensuite chaque tour le dragons va choisir un cochon au hasard et va lui infliger entre 5 et 20 points de dégâts.
Puis ensuite tous les cochons VIVANT vont attaquer le dragon pour les infliger des dégâts entre 1 et 5.
Si une créature voit sa vie être égale ou plus petite que 0 alors elle meurt.
Il faut donc indiquer à chaque tour:
- Le numéro du tour
- Les dégâts totaux infligés au dragons
- Les dégâts que s’est pris le cochon
- Si il y a un mort il faut le dire
- Si le dragon est mort ou que tous les cochons le sont il faut indiquer qui a gagné */


#define MIN_DAMAGE_DRAGON 5
#define MAX_DAMAGE_DRAGON 20

#define MIN_DAMAGE_PIG 1
#define MAX_DAMAGE_PIG 5

bool DragonTurn(std::vector<int>& pigs);
int PigsTurn(std::vector<int>& pigs, int dragonHealth);


bool DragonTurn(std::vector<int>& pigs)
{
	int randomDragonDamage = (rand() % MAX_DAMAGE_DRAGON) + MIN_DAMAGE_DRAGON;
	int numberPig = -1;

	// We search for an alive pig
	do
	{
		numberPig = rand() % pigs.size();
	} while (pigs.at(numberPig) <= 0);
	std::cout << "\n----- Le dragon attaque le cochon " << numberPig << " ----\n";

	pigs.at(numberPig) -= randomDragonDamage;

	std::cout << "Degats generes " << randomDragonDamage << "\n";

	if (pigs.at(numberPig) <= 0)
	{
		std::cout << "Le cochon (" << numberPig << ") meurt !\n";
		for (auto pig : pigs)
		{
			if (pig > 0)
				return true;
		}

		return false;
	}
	return true;
}

int PigsTurn(std::vector<int>& pigs, int dragonHealth)
{
	int totalPigsDamage = 0;
	std::cout << "\n----- Les cochons attaquent ! -----\n";
	for (auto pig : pigs)
	{
		if (pig > 0)
			totalPigsDamage += rand() % MAX_DAMAGE_PIG + MIN_DAMAGE_PIG;
	}

	std::cout << "Degats generes " << totalPigsDamage << "\n";
	dragonHealth -= totalPigsDamage;

	if (dragonHealth <= 0)
		std::cout << "Le dragon meurt !\n";

	return dragonHealth;
}

int main()
{
	//Init random clock
	srand(time(0));

	std::vector<int> pigs(10, 10); // 10 pigs with 10 health
	bool atLeastOnePigAlive = true;
	int dragonHealth = 100;

	int numTurn = 0;

	while (atLeastOnePigAlive || dragonHealth > 0)
	{
		numTurn++;

		std::cout << "\n\n----------------------------\n";
		std::cout << "----------- Tour " << numTurn << "--------\n";

		atLeastOnePigAlive = DragonTurn(pigs);
		dragonHealth = PigsTurn(pigs, dragonHealth);
	}

	system("pause");
	return EXIT_SUCCESS;
}