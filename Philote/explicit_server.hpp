

/**
 * @brief Server base class for an explicit discipline.
 *
 * This class should be inherited from by analysis discipline developers to
 * create analysis servers.
 */
class ExplicitServer
{
    //! Constructor
    ExplicitServer();

    //! Destructor
    ~ExplicitServer();

    /**
     * @brief Sets up the analysis server before any function or gradient
     * evaluation.
     *
     */
    void Setup();

    /**
     * @brief Function evaluation for the discipline.
     *
     * This function should be overridden by the developer of the discipline.
     */
    virtual void Compute();

    /**
     * @brief Function evaluation for the discipline.
     *
     * This function should be overridden by the developer of the discipline, if
     * applicable (not every discipline can provide partials).
     */
    virtual void ComputePartials();
};