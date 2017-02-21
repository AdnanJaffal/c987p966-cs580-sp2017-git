/*
 * product.hpp
 *
 *  Created on: Apr 12, 2016
 *      Author: Adnan Jaffal
 */

#ifndef _PRODUCT_HPP_
#define _PRODUCT_HPP_

#include <string>
#include <vector>
#include <iostream>

class ProductBatch;

enum Category { PERISHABLE, NONPERISHABLE };

class Product
{
 public:
   // constructor and destructor
   Product(int id, std::string name, Category category, unsigned int storage);
   ~Product();

   // transfer of products
   bool receive(unsigned long amount, unsigned int day_received);
   bool ship_from_batch (unsigned long amount, unsigned int b);

   // accessors
   int product_id (void) const;
   std::string product_name (void) const;
   Category category (void) const;
   unsigned int storage_life (void) const;
   unsigned int num_batches (void) const;
   ProductBatch* batch(unsigned int i) const;

   // mutators
   // There is no set_product_id because can't be changed.
   bool set_product_name(std::string name);
   bool set_category_and_storage(Category category, unsigned int days);

 private:
   // data members
   unsigned int m_storage_life;
   int m_product_id;
   std::string m_product_name;
   Category m_category;
   std::vector<ProductBatch*> m_batches;
};

#endif
