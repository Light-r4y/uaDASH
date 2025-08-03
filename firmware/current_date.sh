#!/bin/bash

# This script generates a C header file 'build_info.h'
# which contains the current date as a build tag.

BUILD_INFO_FILE="build_info.h"

# Get the current date in YYYY-MM-DD format
# You can change the format string below if you prefer a different date format.
# For example, to get 'YYYY-MM-DD-HH-MM', use `date +'%Y-%m-%d-%H-%M'`.
CURRENT_DATE=$(date +'%Y-%m-%d')

# The `DASH_TAG` will be the current date enclosed in double quotes.
DASH_TAG_VALUE="\"${CURRENT_DATE}\""

# Write the #define statement to the file.
# The 'DASH_TAG' will be defined with the current date string.
echo "#define DASH_TAG ${DASH_TAG_VALUE}" > "${BUILD_INFO_FILE}"

# Print a confirmation message to the console.
echo "Created '${BUILD_INFO_FILE}' with DASH_TAG set to: ${DASH_TAG_VALUE}"