#include<stdio.h>
#include<stdlib.h>
#include<string>

struct BoxaAudio
{
	char* producator;
	float pret;
	int frecventaMaxima;
};

struct Nod {
	Nod* next;
	BoxaAudio info;
	Nod* prev;
};

struct ListaDubla {
	Nod* cap;
	Nod* coada;
};

BoxaAudio initBoxa(const char* producator, float pret, float frecventaMax) {
	BoxaAudio b;
	b.frecventaMaxima = frecventaMax;
	b.pret = pret;
	b.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(b.producator, producator);
	return b;
}

void afisareBoxa(BoxaAudio b) {
	printf("Boxa e produsa de %s, costa %5.2f lei si are o frecv. maxima de %d Mhz.\n", b.producator, b.pret, b.frecventaMaxima);
}

void adaugareNodInLista(ListaDubla& lista, BoxaAudio b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initBoxa(b.producator, b.pret, b.frecventaMaxima);
	if (lista.cap) {
		nou->next = lista.cap;
		lista.cap->prev = nou;
		lista.cap = nou;
		nou->prev = NULL;


	}
	else {
		lista.cap = nou;
		lista.coada = nou;
		lista.cap->prev = NULL;
		lista.coada->next = NULL;
	}
}

void afisareListaDubla(Nod* lista) {
	if (lista) {
		while (lista) {
			afisareBoxa(lista->info);
			lista = lista->next;
		}
	}
	else printf("Lista este goala sau a fost stearsa!");
}

void stergereBoxaCuConditie(ListaDubla& lista, const char* numeProducator) {
	if (lista.cap) {
		Nod* aux = lista.cap;
		while (aux && strcmp(aux->info.producator, numeProducator) != 0)
		{
			aux = aux->next;
		}
		if (aux->prev) {
			if (aux->next) {
				aux->prev->next = aux->next;
				aux->next->prev = aux->prev;
			}
			else {
				lista.coada = aux->prev;
				aux->prev->next = NULL;
			}
			free(aux->info.producator);
			free(aux);

		}
		else {
			aux->next->prev = NULL;
			lista.cap = aux->next;
			free(aux->info.producator);
			free(aux);
		}
	}
}

void main() {
	ListaDubla* lista = NULL;
	lista = (ListaDubla*)malloc(sizeof(ListaDubla));
	lista->cap = NULL;
	lista->coada = NULL;
	BoxaAudio b1 = initBoxa("JBL Go 2", 99.8, 20000);
	BoxaAudio b2 = initBoxa("Harmann Kardon", 998, 25000);
	BoxaAudio b3 = initBoxa("Sony SRS-X2", 433.50, 22000);
	BoxaAudio b4 = initBoxa("Philips", 245.50, 22000);
	BoxaAudio b5 = initBoxa("Google Assistant", 1280.99, 20000);

	adaugareNodInLista(*lista, b1);
	adaugareNodInLista(*lista, b2);
	adaugareNodInLista(*lista, b3);
	adaugareNodInLista(*lista, b4);
	adaugareNodInLista(*lista, b5);

	afisareListaDubla((*lista).cap);

	stergereBoxaCuConditie(*lista, "Google Assistant");
	printf("\n\n");

	afisareListaDubla((*lista).cap);

}