#pragma once

#include <string>
#include <map>
#include <utility>
#include <Philote/array.h>
#include <Philote/discrete_array.h>

namespace philote
{
    /**
     * @brief Server base class for an explicit discipline.
     *
     * This class should be inherited from by analysis discipline developers to
     * create analysis servers.
     */
    class ExplicitServer
    {
    public:
        //! Constructor
        ExplicitServer();

        //! Destructor
        ~ExplicitServer();

        /**
         * @brief Sets up the analysis server before any function or gradient
         * evaluation.
         *
         * This function should be overridden by the developer of the discipline.
         */
        virtual void Setup();

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

    private:
        //! names of all functions defined for this discipline
        std::vector<std::string> funcs_;

        //! shape of all functions defined for this discipline
        std::map<std::string, std::vector<size_t>> funcs_shape_;

        //! units of all functions defined for this discipline
        std::map<std::string, std::string> funcs_units_;

        //! names of all discrete functions defined for this discipline
        std::vector<std::string> discrete_funcs_;

        //! shape of all discrete functions defined for this discipline
        std::map<std::string, std::vector<size_t>> discrete_funcs_shape_;

        //! shape of all discrete functions defined for this discipline
        std::map<std::string, std::string> discrete_funcs_units_;

        //! names of all variables defined for this discipline
        std::vector<std::string> vars_;

        //! shape of all variables defined for this discipline
        std::map<std::string, std::vector<size_t>> vars_shape_;

        //! units of all variables defined for this discipline
        std::map<std::string, std::string> vars_units_;

        //! names of all discrete variables defined for this discipline
        std::vector<std::string> discrete_vars_;

        //! shape of all discrete variables defined for this discipline
        std::map<std::string, std::vector<size_t>> discrete_vars_shape_;

        //! units of all discrete variables defined for this discipline
        std::map<std::string, std::string> discrete_vars_units_;

        //! vector of all defined partials
        std::vector<std::pair<std::string, std::string>> partials_;
    };
} // namespace philote