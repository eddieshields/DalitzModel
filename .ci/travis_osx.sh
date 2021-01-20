echo -en 'travis_fold:start:script.build\\r'
echo "Building..."
echo "Building under OS: $TRAVIS_OS_NAME"

mkdir -p build
cd build
echo "CMake-ing, CXX = $CXX"
cmake .. 
echo "Building ..."
make
cd ..
echo "Running test job ..."
./build/ToyGenerator