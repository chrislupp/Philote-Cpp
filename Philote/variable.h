/*
    Philote C++ Bindings

    Copyright 2022-2023 Christopher A. Lupp

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    This work has been cleared for public release, distribution unlimited, case
    number: AFRL-2023-5716.

    The views expressed are those of the authors and do not reflect the
    official guidance or position of the United States Government, the
    Department of Defense or of the United States Air Force.

    Statement from DoD: The Appearance of external hyperlinks does not
    constitute endorsement by the United States Department of Defense (DoD) of
    the linked websites, of the information, products, or services contained
    therein. The DoD does not exercise any editorial, security, or other
    control over the information you may find at these locations.
*/
#pragma once

#include <string>
#include <map>
#include <vector>

#include <data.pb.h>
#include <disciplines.grpc.pb.h>

namespace philote
{
    /**
     * @brief A class for storing continuous and discrete variables
     *
     */
    class Variable
    {
    public:
        /**
         * @brief Construct a new Variables object
         *
         */
        Variable() = default;

        /**
         * @brief Construct a new Variable object
         *
         * @param type
         * @param shape
         */
        Variable(const philote::VariableType &type,
                 const std::vector<size_t> &shape);

        /**
         * @brief Construct a new Variable object
         *
         * @param meta
         */
        explicit Variable(const philote::VariableMetaData &meta);

        /**
         * @brief Construct a new Variable object
         *
         * @param meta
         */
        explicit Variable(const philote::PartialsMetaData &meta);

        /**
         * @brief Destroy the Variables object
         *
         */
        ~Variable() = default;

        /**
         * @brief Assigns a segment of the array given a subvector
         *
         * @param start starting index of the segment
         * @param end ending index of the segment
         * @param data data to be assigned to the segment
         */
        void Segment(const size_t &start, const size_t &end,
                     const std::vector<double> &data);

        /**
         * @brief Retrieves a reference to a segment of the array given a
         * subvector
         *
         * @param start
         * @param end
         * @return std::vector<Type>&
         */
        std::vector<double> Segment(const size_t &start, const size_t &end) const;

        /**
         * @brief Returns the shape of the array
         *
         * @return std::vector<size_t> vector containing the length of the
         * individual dimensions
         */
        std::vector<size_t> Shape() const;

        /**
         * @brief Returns the size of the array.
         *
         * @return size_t size of the array
         */
        size_t Size() const;

        /**
         * @brief Returns the value of the array at a given index
         *
         * @param indices indices at which the array should be accessed
         * @return double value of the array at the given indices
         */
        double operator()(const size_t &i) const;

        /**
         * @brief Returns the value of the array at a given index
         *
         * @param indices indices at which the array should be accessed
         * @return double value of the array at the given indices
         */
        double &operator()(const size_t &i);

		/**
         * @brief Create a Chunk of the variable
         *
         * @param start
         * @param end
         * @return philote::Array
         */
		philote::Array CreateChunk(const size_t &start, const size_t &end) const;

        /**
         * @brief Sends the variable from the client to the server
         *
         * @param stream
         */
        void Send(std::string name,
                  std::string subname,
                  grpc::ClientReaderWriter<::philote::Array, ::philote::Array> *stream,
                  const size_t &chunk_size) const;

        /**
         * @brief Sends the variable from the server to the client
         *
         * @param stream
         */
        void Send(std::string name,
                  std::string subname,
                  grpc::ServerReaderWriter<::philote::Array, ::philote::Array> *stream,
                  const size_t &chunk_size) const;

        /**
         * @brief Assigns a chunk to the variable
         *
         * @param stream
         * @param chunk_size
         */
        void AssignChunk(const Array &data);

    private:
        //! variable type
        philote::VariableType type_;

        //! array shape
        std::vector<size_t> shape_;

        //! raw data (serialized, row major)
        std::vector<double> data_;

        //! raw discrete data (serialized, row major)
        std::vector<int64_t> discrete_data_;
    };

    typedef std::map<std::string, philote::Variable> Variables;
    typedef std::map<std::pair<std::string, std::string>, philote::Variable> Partials;
}