#ifndef SICT__AidApp_H_
#define SICT__AidApp_H_

#include "Product.h"
#include "general.h"
#include "AmaProduct.h"
#include "AmaPerishable.h"

namespace sict {

		class AidApp {
				char filename_[256];
				Product* product_[MAX_NO_RECS];
				std::fstream datafile_;
				int noOfProducts_;

				//private member functions
		public:
				void pause()const;
				int menu();
				void loadRecs();
				void saveRecs();
				void listProducts()const;
				int SearchProducts(const char* sku)const;
				void addQty(const char* sku);
				void addProduct(bool isPerishable);
				

		
				//constructor
				AidApp(const char*);
				int run();

		};


}
#endif