
/**
 * @brief Client class for calling a remote explicit discipline.
 *
 * This class may be inherited from or used by MDO framework developers.
 * However, it is a fully functional Philote MDO client.
 */
class ExplicitClient
{
    //! Constructor
    ExplicitClient();

    //! Destructor
    ~ExplicitClient();

    /**
     * @brief Calls the setup function on the remote analysis server.
     *
     */
    void RemoteSetup();

    /**
     * @brief Calls the remote analysis server function evaluation via gRPC.
     *
     * Unlike the analysis server, this function does not need to be overridden,
     * as it contains all logic necessary to retrieve the remote function
     * evaluation.
     */
    void RemoteCompute();

    /**
     * @brief Calls the remote analysis server function evaluation via gRPC.
     *
     * Unlike the analysis server, this function does not need to be overridden,
     * as it contains all logic necessary to retrieve the remote function
     * evaluation.
     */
    void RemoteComputePartials();
};