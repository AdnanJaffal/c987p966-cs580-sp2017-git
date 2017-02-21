/*
 * productbatch.hpp
 *
 *  Created on: Apr 12, 2016
 *      Author: Adnan Jaffal
 */

#ifndef PRODUCTBATCH_HPP_
#define PRODUCTBATCH_HPP_

#include <iostream>

class Product;

class ProductBatch {
 private:
   Product& m_product;
   unsigned long m_num_in_stock;
   unsigned int m_received_on, m_expires_on;

 public:
   // Constructor
   ProductBatch (Product& product, unsigned long stock, unsigned int received, unsigned int storage);

   // Destructor
   ~ProductBatch ();

   // Accessors
   unsigned long num_in_stock (void) const;
   unsigned int received_on (void) const;
   unsigned int expires_on (void) const;
   Product& product (void) const;

   // Mutators
   bool ship(unsigned long amount);
   bool expire_process(void);
};



#endif /* PRODUCTBATCH_HPP_ */
