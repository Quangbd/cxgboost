//
// Created by quangbd on 23/02/2021.
//

#ifndef CXGBOOST_MODEL_H
#define CXGBOOST_MODEL_H

#include <cstdio>
#include <cstdlib>

extern "C" {
#include "includes/xgboost/c_api.h"
}

#define safe_xgboost(call) {  \
  int err = (call); \
  if (err != 0) { \
    fprintf(stderr, "%s:%d: error in %s: %s\n", __FILE__, __LINE__, #call, XGBGetLastError());  \
    exit(1); \
  } \
}

class Model {
private:
    BoosterHandle booster{};
    const char *model_path;

public:
    Model(const char *model_path, bool is_train);

    static Model &get_instance(const char *model_path, bool refresh);

    const char *fit(const char *train_path, const char *test_path, const char *max_depth = "15",
                    const char *learning_rate = "0.15", const char *alpha = "3",
                    const char *n_estimators = "50", int num_of_iterations = 500);

    float predict(const float *features, int size);

    void load_model();

    void close();
};


#endif //CXGBOOST_MODEL_H
