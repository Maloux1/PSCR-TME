// FAUTE le fichier .h doit etre inclus pour que le compilateur puisse voir la structure de données
#include "List.h"

namespace pr {

// ******************* Chainon
Chainon::Chainon (const std::string & data, Chainon * next):data(data),next(next) {};

size_t Chainon::length() {
	// FAUTE on corrige la fonction length pour qu'elle appelle la fonction length du chainon suivant et pas celle de this. pour éviter une boucle infinie.
	if (next != nullptr) {
		return 1 + (*next).length();
	}
	return 1;
}

// FAUTE il manque le const donc la fonction n'est pas reconnue par rapport à celle du fichier List.h
void Chainon::print (std::ostream & os) const {
	os << data ;
	if (next != nullptr) {
		os << ", ";
		// FAUTE on déplace l'instruction suivante dans le if, sinon la fonction recursive n'a pas de condition de sortie
		next->print(os);
	}
}

// ******************  List
const std::string & List::operator[] (size_t index) const  {
	Chainon * it = tete;
	for (size_t i=0; i < index ; i++) {
		// FAUTE il faut tester si l'élement next est bien accessible et sinon on retourne la chaine vide.
		if (it->next == nullptr) {
      return "";
		}
		it = it->next;
	}
	return it->data;
}

void List::push_back (const std::string& val) {
	if (tete == nullptr) {
		tete = new Chainon(val);
	} else {
		Chainon * fin = tete;
		while (fin->next) {
			fin = fin->next;
		}
		fin->next = new Chainon(val);
	}
}

/* FAUTE on supprime le double de la methode push front car on ne peut pas la definir deux fois
 * void List::push_front (const std::string& val) {
	tete = new Chainon(val,tete);
}
 *
 * */
// FAUTE la methode empty appartient à List, il faut le préciser
bool List::empty() {
	return tete == nullptr;
}

size_t List::size() const {
	if (tete == nullptr) {
		return 0;
	} else {
		return tete->length();
	}
}


std::ostream & operator<< (std::ostream & os, const pr::List & vec)
{
	os << "[";
	if (vec.tete != nullptr) {
		vec.tete->print (os) ;
	}
	os << "]";
	return os;
}

// FAUTE la fonction doit faire partie du meme namespace que la classe
} // namespace pr

