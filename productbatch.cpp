/*
 * productbatch.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: Adnan Jaffal
 */

#include "productbatch.hpp"
#include "product.hpp"

// Constructor
ProductBatch::ProductBatch(Product& product, unsigned long stock, unsigned int received,
		unsigned int storage) :
	m_product(product), m_num_in_stock(stock), m_received_on(received) {
	Category state = m_product.category();

	//std::cout << "Stock: " << m_num_in_stock << ", Received: " << m_received_on << ", State: " << state;
	if (state == PERISHABLE) {
		m_expires_on = storage + m_received_on;
	} else {
		m_expires_on = 0;
	}
}

// Destructor
ProductBatch::~ProductBatch()
{}

// Accessors
unsigned long ProductBatch::num_in_stock(void) const {
   return m_num_in_stock;
}

unsigned int ProductBatch::received_on(void) const {
	return m_received_on;
}

unsigned int ProductBatch::expires_on(void) const {
	return m_expires_on;
}

Product& ProductBatch::product(void) const {
	return m_product;
}

// Mutators
bool ProductBatch::ship(unsigned long amount)
{
   bool done = true;

   if (amount <= m_num_in_stock)
   {
      m_num_in_stock -= amount;
   }
   else
   {
      done = false;
   }

   return done;
}

bool ProductBatch::expire_process(void) {
	bool done = true;

	if (m_num_in_stock > 0) {
		done = ship(m_num_in_stock);
	} else {
		done = false;
	}

	return done;
}
