//
// Created by quangbd on 23/02/2021.
//

#include "Model.h"
#include "logging.h"

Model::Model(const char *model_path, bool is_train) {
    this->model_path = model_path;
    if (!is_train) {
        load_model();
    }
}

Model &Model::get_instance(const char *model_path, bool refresh) {
    static Model model(model_path, false);
    if (refresh) {
        model.load_model();
    }
    return model;
}

const char *Model::fit(const char *train_path, const char *test_path, const char *max_depth,
                       const char *learning_rate, const char *alpha, const char *n_estimators, int num_of_iterations) {
    DMatrixHandle train_data;
    safe_xgboost(XGDMatrixCreateFromFile(train_path, 0, &train_data))

    DMatrixHandle test_data;
    safe_xgboost(XGDMatrixCreateFromFile(test_path, 0, &test_data))

    DMatrixHandle eval_d_mats[2] = {train_data, test_data};
    safe_xgboost(XGBoosterCreate(eval_d_mats, 2, &booster))
    safe_xgboost(XGBoosterSetParam(booster, "max_depth", max_depth))
    safe_xgboost(XGBoosterSetParam(booster, "learning_rate", learning_rate))
    safe_xgboost(XGBoosterSetParam(booster, "alpha", alpha))
    safe_xgboost(XGBoosterSetParam(booster, "n_estimators", n_estimators))

    const char *eval_names[2] = {"train", "test"};
    const char *eval_result = nullptr;

    for (int i = 0; i < num_of_iterations; ++i) {
        safe_xgboost(XGBoosterUpdateOneIter(booster, i, train_data));
        safe_xgboost(XGBoosterEvalOneIter(booster, i, eval_d_mats, eval_names, 2, &eval_result));
        LOG_INFO("%s\n", eval_result);
    }

    size_t result_len = strlen(eval_result);
    char *train_result = (char *) malloc(result_len + 1);
    train_result[result_len] = '\0';
    strcpy((char *) &train_result[0], &eval_result[0]);

    safe_xgboost(XGBoosterSaveModel(booster, model_path))

    close();
    XGDMatrixFree(train_data);
    XGDMatrixFree(test_data);
    LOG_INFO("training has been completed");
    return train_result;
}

float Model::predict(const float *features, int size) {
    DMatrixHandle d_matrix;
    safe_xgboost(XGDMatrixCreateFromMat(features, 1, size, 0, &d_matrix));

    bst_ulong output_length;
    const float *output_result;
    safe_xgboost(XGBoosterPredict(booster, d_matrix, 0, 0, 0, &output_length, &output_result))
    LOG_INFO("prediction = %f \n", output_result[0]);
    XGDMatrixFree(d_matrix);
    return output_result[0];
}

void Model::load_model() {
    safe_xgboost(XGBoosterCreate(nullptr, 0, &booster));
    safe_xgboost(XGBoosterLoadModel(booster, model_path));
    bst_ulong num_of_features = 0;
    safe_xgboost(XGBoosterGetNumFeature(booster, &num_of_features));
    LOG_INFO("num_feature: %lu\n", (unsigned long) (num_of_features));
}

void Model::close() {
    XGBoosterFree(booster);
}
