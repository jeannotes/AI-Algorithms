COPTS = [
    "-std=c++11",
    "-fPIC",
    "-fopenmp",
]
LINK_OPTS = []
DEFINES = [
]

cc_library(
    name = "svm",
    srcs = [
        "svm.cpp",
    ],
    hdrs = [
        "svm.h",
    ],
)

cc_binary(
    name = "svm-scale",
    srcs = [
        "svm-scale.c"
    ],
    deps = [
        "//:svm",
    ],
)


cc_binary(
    name = "svm-predict",
    srcs = [
        "svm-predict.c"
    ],
    deps = [
        "//:svm",
    ],
)

cc_binary(
    name = "svm-train",
    srcs = [
        "svm-train.c"
    ],
    deps = [
        "//:svm",
    ],
)