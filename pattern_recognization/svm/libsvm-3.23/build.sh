#!/bin/bash

function help() {
  echo "Usage: ./build.sh <command>"
  echo ""
  echo "Available commands:"
  echo "  deps             Fetch dependencies of client_adapter"
  echo "  test             Build client_adapter for test environment."
  echo "  release          Build client_adapter for release environment."
  echo "  fetch_commit  Generate version.yml for client_adapter which contains commit information of dependencies."
}

function scale() {
  bazel build //:svm-scale --cpu=k8 -c opt  \
    --copt=-g --copt=-O3 
}

function predict() {
  bazel build //:svm-predict --cpu=k8 -c opt  \
    --copt=-g --copt=-O3 
}

function trainf() {
  bazel build //:svm-train --cpu=k8 -c opt  \
    --copt=-g --copt=-O3 
}
function train() {
  bazel build //:svm-train 
}

$@