/*
 * product.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: Adnan Jaffal
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "product.hpp"
#include "productbatch.hpp"

// Constructor and destructor
Product::Product(int id, std::string name, Category category, unsigned int storage) :
m_product_id(id), m_product_name(name), m_category(category)
{
	if (category == PERISHABLE) {
		m_storage_life = storage;
	} else {
		m_storage_life = 0;
	}
}

Product::~Product()
{}

// Transfer of products
bool Product::receive(unsigned long amount, unsigned int day_received)
{
	//std::cout << "Amount: " << amount << ", day received: " << day_received;
   ProductBatch* batch = new ProductBatch(*this, amount, day_received, m_storage_life);
   m_batches.push_back(batch);

   return true;
}

bool Product::ship_from_batch (unsigned long amount, unsigned int b) {
	bool done = true;

	if (m_batches[b]) {
		done = m_batches[b]->ship(amount);

		if (m_batches[b]->num_in_stock() == 0) {
			for (unsigned int x = b ; x < (m_batches.size() - 1) ; x++) {
				m_batches[x] =  m_batches[x+1];
			}

			m_batches.pop_back();
		}
	} else {
		done = false;
	}

	return done;
}

// Accessors
int Product::product_id(void) const
{
   return m_product_id;
}

std::string Product::product_name(void) const
{
   return m_product_name;
}

Category Product::category(void) const
{
   return m_category;
}

unsigned int Product::storage_life(void) const {
	return m_storage_life;
}

unsigned int Product::num_batches(void) const {
	return m_batches.size();
}

ProductBatch* Product::batch(unsigned int i) const {
	//std::cout << "i: " << i;
	if (m_batches[i]) {
		//std::cout << "Stock: " << m_batches[i]->num_in_stock() << ", Received: " << m_batches[i]->received_on();
		return m_batches[i];
	} else {
		return NULL;
	}
}

// Mutators
bool Product::set_product_name(std::string name)
{
   m_product_name = name;

   return true;
}

bool Product::set_category_and_storage(Category category, unsigned int days)
{
   bool done = false;

   if (category == PERISHABLE) {
	   if (days > 0) {
		   m_category = category;
		   m_storage_life = days;
		   done = true;
	   }
   } else {
	   if (days == 0) {
		   m_category = category;
		   m_storage_life = days;
		   done = true;
	   }
   }

   return done;
}


