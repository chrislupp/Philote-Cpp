#include <Philote/variable.h>

using grpc::ClientReaderWriter;
using grpc::ServerReaderWriter;
using std::map;
using std::shared_ptr;
using std::string;
using std::vector;

using namespace philote;

Variable::Variable(const std::string &name,
                   const philote::VariableType &type,
                   const std::vector<size_t> &shape,
                   const std::string &units)
{
    // assign the array shape
    shape_ = shape;

    // serialized array size
    size_t size = 1;
    for (size_t i = 0; i < shape_.size(); i++)
        size *= shape_[i];

    // initialize the array from the shape input
    data_.resize(size);
}

void Variable::Segment(const size_t &start, const size_t &end,
                       const std::vector<double> &data)
{
    // check that the segment matches length of (end - start)
    if ((end - start) + 1 != data.size())
    {
        std::string expected = std::to_string((end - start) + 1);
        std::string actual = std::to_string(data.size());
        throw std::length_error("Vector data has incompatable length. Should be " +
                                expected + ", but received " + actual + ".");
    }

    // assign the segment
    for (size_t i = 0; i < (end - start) + 1; i++)
        data_[start + i] = data[i];
}

std::vector<double> Variable::Segment(const size_t &start, const size_t &end)
{
    std::vector<double> data(end - start + 1);

    // check that the segment matches length of (end - start)
    if ((end - start) + 1 != data_.size())
    {
        std::string expected = std::to_string((end - start) + 1);
        std::string actual = std::to_string(data.size());
        throw std::length_error("Vector data has incompatable length. Should be " +
                                expected + ", but received " + actual + ".");
    }

    // assign the segment
    for (size_t i = 0; i < (end - start) + 1; i++)
        data[i] = data_[start + i];

    return data;
}

std::vector<size_t> Variable::Shape() const
{
    return shape_;
}

size_t Variable::Size() const
{
    return data_.size();
}

double Variable::operator()(const size_t &i) const
{
    return data_[i];
}

void Variable::Send(shared_ptr<ClientReaderWriter<Array, Array>> stream)
{
    ::philote::Array inputs;

    inputs.set_name(name_);

    // chunk start and end indices within the serialized array
    inputs.set_start(0);
    inputs.set_end(1);

    stream->Write(inputs);
}

void Variable::Send(ServerReaderWriter<Array, Array> *stream)
{
    ::philote::Array inputs;

    inputs.set_name(name_);

    // chunk start and end indices within the serialized array
    inputs.set_start(0);
    inputs.set_end(1);

    stream->Write(inputs);
}