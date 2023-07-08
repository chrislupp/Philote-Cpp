#pragma once

#include <string>
#include <map>
#include <utility>
#include <Philote/array.h>
#include <Philote/options.h>
#include <Philote/variable_meta.h>
#include <Philote/variables.h>
#include <Philote/partials.h>

#include <explicit.grpc.pb.h>

namespace philote
{
    /**
     * @brief Server base class for an explicit discipline.
     *
     * This class should be inherited from by analysis discipline developers to
     * create analysis servers.
     */
    class ExplicitServer : public ExplicitDiscipline::Service
    {
    public:
        //! Constructor
        ExplicitServer();

        //! Destructor
        ~ExplicitServer();

        /**
         * @brief Set the stream options provided by the client
         *
         * @param context
         * @param request
         * @param response
         * @return ::grpc::Status
         */
        virtual grpc::Status SetStreamOptions(grpc::ServerContext *context,
                                              const ::Options *request,
                                              google::protobuf::Empty *response) override;

        virtual grpc::Status DefineVariables(grpc::ServerContext *context,
                                             const google::protobuf::Empty *request,
                                             grpc::ServerWriter<::VariableMetaData> *writer) override;

        virtual grpc::Status DefinePartials(grpc::ServerContext *context,
                                            const google::protobuf::Empty *request,
                                            grpc::ServerWriter<::PartialsMetaData> *writer) override;

        virtual grpc::Status Functions(grpc::ServerContext *context,
                                       grpc::ServerReaderWriter<::Array, ::Array> *stream) override;

        virtual grpc::Status Gradient(grpc::ServerContext *context,
                                      grpc::ServerReaderWriter<::Array, ::Array> *stream) override;

        /**
         * @brief Sets up the analysis server before any function or gradient
         * evaluation.
         *
         * This function should be overridden by the developer of the
         * discipline.
         */
        virtual void Setup();

        /**
         * @brief Defines the partials for this discipline.
         *
         * This function should be overridden by the developer of the
         * discipline.
         */
        virtual void SetupPartials();

        /**
         * @brief Function evaluation for the discipline.
         *
         * This function should be overridden by the developer of the
         * discipline.
         *
         * @param inputs input variables for the discipline (continuous and
         * discrete)
         * @return philote::Variables
         */
        virtual philote::Variables Compute(const philote::Variables &inputs);

        /**
         * @brief Gradient evaluation for the discipline.
         *
         * This function should be overridden by the developer of the
         * discipline, if applicable (not every discipline can provide
         * partials).
         *
         * @param inputs input variables for the discipline (continuous and
         * discrete)
         */
        virtual philote::Partials ComputePartials(const philote::Variables &inputs);

    private:
        //! Options that control how data is streamed
        StreamOptions stream_opts_;

        //! Variable meta data (this includes, inputs, outputs, and residuals)
        VariableMeta vars_;
    };
} // namespace philote