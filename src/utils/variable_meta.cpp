#include <Philote/variable_meta.h>

using std::string;
using std::vector;
using namespace philote;

void VariableMeta::AddInput(const std::string &name,
                            const std::vector<int64_t> &shape,
                            const std::string &units)
{
    // add to the type map
    type_[name] = VariableType::kInput;

    // add to the shape map
    shape_[name] = shape;

    // add to the units map
    units_[name] = units;
}

void VariableMeta::AddDiscreteInput(const std::string &name,
                                    const std::vector<int64_t> &shape,
                                    const std::string &units)
{
    // add to the type map
    type_[name] = VariableType::kDiscreteInput;

    // add to the shape map
    shape_[name] = shape;

    // add to the units map
    units_[name] = units;
}

void VariableMeta::AddOutput(const std::string &name,
                             const std::vector<int64_t> &shape,
                             const std::string &units)
{
    // add to the type map
    type_[name] = VariableType::kOutput;

    // add to the shape map
    shape_[name] = shape;

    // add to the units map
    units_[name] = units;
}

void VariableMeta::AddDiscreteOutput(const std::string &name,
                                     const std::vector<int64_t> &shape,
                                     const std::string &units)
{
    // add to the type map
    type_[name] = VariableType::kDiscreteOutput;

    // add to the shape map
    shape_[name] = shape;

    // add to the units map
    units_[name] = units;
}

size_t VariableMeta::NumVariables() const
{
    return type_.size();
}

vector<string> VariableMeta::ListVariables() const
{
    // list of all keys (variables)
    std::vector<std::string> keys;

    for (const auto &pair : type_)
    {
        keys.push_back(pair.first);
    }

    return keys;
}

const VariableType &VariableMeta::Type(const string &name)
{
    return type_[name];
}

const std::vector<int64_t> &VariableMeta::Shape(const string &name)
{
    return shape_[name];
}

const string &VariableMeta::Units(const string &name)
{
    return units_[name];
}