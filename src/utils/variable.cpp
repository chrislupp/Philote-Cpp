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
                   const std::vector<size_t> &shape)
{
    type_ = type;
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

Array Variable::CreateChunk(const size_t &start, const size_t end)
{
    Array out;
    out.set_name(name_);
    out.set_start(start);
    out.set_end(end);

    // set the data
    if (type_ == kInput or type_ == kOutput or type_ == kResidual)
    {
        for (const double &value : Segment(start, end))
        {
            out.add_continuous(value);
        }
    }
    else if (type_ == kDiscreteInput or type_ == kDiscreteOutput)
    {
        /* code */
    }

    return out;
}

void Variable::Send(shared_ptr<ClientReaderWriter<Array, Array>> stream,
                    const size_t &chunk_size)
{
    Array array;
    size_t start, end;
    size_t n = Size();

    if (n == 1)
    {
        start = 0;
        end = 1;
        array = CreateChunk(start, end);
        stream->Write(array);
    }
    else
    {
        // find the chunk indices and create the chunk
        for (size_t i = 0; i < n / chunk_size; i++)
        {
            start = i * chunk_size;
            end = start + chunk_size;
            if (end > n)
            {
                end = n;
            }

            array = CreateChunk(start, end);
            stream->Write(array);
        }
    }
}

void Variable::Send(ServerReaderWriter<Array, Array> *stream,
                    const size_t &chunk_size)
{
    Array array;
    size_t start = 0, end;
    size_t n = Size();

    if (n == 1)
    {
        start = 0;
        end = 1;
        array = CreateChunk(start, end);
        stream->Write(array);
    }
    else
    {
        // find the chunk indices and create the chunk
        for (size_t i = 0; i < n / chunk_size; i++)
        {
            start = i * chunk_size;
            end = start + chunk_size;
            if (end > n)
            {
                end = n;
            }

            array = CreateChunk(start, end);
            stream->Write(array);
        }
    }
}