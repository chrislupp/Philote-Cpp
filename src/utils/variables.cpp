#include <Philote/variables.h>

using std::string;
using std::vector;
using namespace philote;

VariableMeta::VariableMeta() {}

VariableMeta::~VariableMeta() {}

void VariableMeta::AddInput(std::string name, std::vector<size_t> shape,
                            std::string units)
{
    // add to the type map
    type_[name] = VariableType::kInput;

    // add to the shape map
    shape_[name] = shape;

    // add to the units map
    units_[name] = units;
}

void VariableMeta::AddDiscreteInput(std::string name, std::vector<size_t> shape,
                                    std::string units)
{
    // add to the type map
    type_[name] = VariableType::kDiscreteInput;

    // add to the shape map
    shape_[name] = shape;

    // add to the units map
    units_[name] = units;
}

void VariableMeta::AddOutput(std::string name, std::vector<size_t> shape,
                             std::string units)
{
    // add to the type map
    type_[name] = VariableType::kOutput;

    // add to the shape map
    shape_[name] = shape;

    // add to the units map
    units_[name] = units;
}

void VariableMeta::AddDiscreteOutput(std::string name, std::vector<size_t> shape,
                                     std::string units)
{
    // add to the type map
    type_[name] = VariableType::kDiscreteOutput;

    // add to the shape map
    shape_[name] = shape;

    // add to the units map
    units_[name] = units;
}