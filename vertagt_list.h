#pragma once

#include "vertagt_aktion.h"
#include <list>

namespace vertagt
{
	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;
		using reverse_iterator = typename std::list<T>::reverse_iterator;
		using const_reverse_iterator = typename std::list<T>::const_reverse_iterator;

		// Konstruktoren
		VListe() = default; // Benoetigt man einen Standardkonstruktor?
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

	};
} // namespace vertagt