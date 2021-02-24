#include "Model.h"
#include "logging.h"

#ifdef __ANDROID__
#include <jni.h>
#else
#endif

extern "C" {
#ifdef __ANDROID__
JNIEXPORT jstring JNICALL
Java_vinai_cc_xgboost_XGBoost_nativeTrain(JNIEnv *env, jobject thiz, jstring train_path,
                                          jstring test_path, jstring model_path) {
    LOG_INFO("Training");
    const char *j_model_path = env->GetStringUTFChars(model_path, nullptr);
    const char *j_train_path = env->GetStringUTFChars(train_path, nullptr);
    const char *j_test_path = env->GetStringUTFChars(test_path, nullptr);

    Model model(j_model_path, true);
    const char *train_result = model.fit(j_train_path, j_test_path);

    env->ReleaseStringUTFChars(model_path, j_model_path);
    env->ReleaseStringUTFChars(train_path, j_train_path);
    env->ReleaseStringUTFChars(test_path, j_test_path);
    return env->NewStringUTF(train_result);
}

JNIEXPORT jfloat JNICALL
Java_vinai_cc_xgboost_XGBoost_nativePredict(JNIEnv *env, jclass clazz, jstring model_path,
                                            jfloatArray signals, jint length, jboolean refresh) {
    LOG_INFO("Predict");
    float *j_float_signals = env->GetFloatArrayElements(signals, nullptr);
    const char *j_model_path = env->GetStringUTFChars(model_path, nullptr);
    Model model = Model::get_instance(j_model_path, refresh);
    float result = model.predict(j_float_signals, length);
    env->ReleaseFloatArrayElements(signals, j_float_signals, 0);
    env->ReleaseStringUTFChars(model_path, j_model_path);
    return result;
}
#else
#endif
}

int main() {
//    Model model("/Users/quangbd/Desktop/model", true);
//    const char *train_result = model.fit("/Users/quangbd/Desktop/train.libsvm",
//              "/Users/quangbd/Desktop/test.libsvm");
//    LOG_INFO("train result - %s\n", train_result);

    Model model = Model::get_instance("/Users/quangbd/Desktop/model", false);
    const float test_feature[12] = {26.0, 31.0, 2.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    model.predict(test_feature, 12);
    model.close();
    return 0;
}
