#!/bin/bash

# Usage: ./split_data.sh input.csv train_percent val_percent test_percent
FILE=$1
TRAIN_P=$2
VAL_P=$3
TEST_P=$4

# Get total lines excluding header
TOTAL_LINES=$(($(wc -l < "$FILE") - 1))
HEADER=$(head -n 1 "$FILE")

# Calculate line counts
TRAIN_COUNT=$((TOTAL_LINES * TRAIN_P / 100))
VAL_COUNT=$((TOTAL_LINES * VAL_P / 100))
TEST_COUNT=$((TOTAL_LINES - TRAIN_COUNT - VAL_COUNT))

echo "Total records: $TOTAL_LINES"
echo "Splitting: $TRAIN_COUNT train, $VAL_COUNT val, $TEST_COUNT test..."

# Shuffle data (excluding header) and save to temp
tail -n +2 "$FILE" | shuf > combined_shuffled.tmp

# Extract sets
echo "$HEADER" > train.csv
head -n "$TRAIN_COUNT" combined_shuffled.tmp >> train.csv

echo "$HEADER" > val.csv
head -n "$((TRAIN_COUNT + VAL_COUNT))" combined_shuffled.tmp | tail -n "$VAL_COUNT" >> val.csv

echo "$HEADER" > test.csv
tail -n "$TEST_COUNT" combined_shuffled.tmp >> test.csv

# Cleanup
rm combined_shuffled.tmp

echo "Done! Files created: train.csv, val.csv, test.csv"
