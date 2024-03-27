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

        void clear()
		{
			p_objekte.clear();
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			return p_objekte.end();
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			return p_objekte.end();
		}

		const_reverse_iterator rbegin() const
		{
			return p_objekte.rbegin();
		}
		const_reverse_iterator rend() const
		{
			return p_objekte.rend();
		}
		reverse_iterator rbegin()
		{
			return p_objekte.rbegin();
		}
		reverse_iterator rend()
		{
			return p_objekte.rend();
		}

		bool empty() const
		{
			return p_objekte.empty();
		}

        // Schreibfunktionen
		void push_back(T obj)
		{
			// Aktionselement fuer PushBack auf Liste erzeugen
			p_aktionen.push_back(make_unique<VPushBack<T>>(p_objekte, std::move(obj)));

		}

		void push_front(T obj)
		{
			// Aktionselement fuer PushBack auf Liste erzeugen
			p_aktionen.push_back(make_unique<VPushFront<T>>(p_objekte, std::move(obj)));

		}

		void erase(iterator it)
		{
			// Aktionselement fuer PushBack auf Liste erzeugen (hier Iterator statt Objekt !)
			p_aktionen.push_back(make_unique<VErase<T>>(p_objekte,it));
		}


	};
} // namespace vertagt