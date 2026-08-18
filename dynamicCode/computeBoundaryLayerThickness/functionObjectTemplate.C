/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019-2021 OpenCFD Ltd.
    Copyright (C) YEAR AUTHOR, AFFILIATION
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "functionObjectTemplate.H"
#define namespaceFoam  // Suppress <using namespace Foam;>
#include "fvCFD.H"
#include "unitConversion.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(computeBoundaryLayerThicknessFunctionObject, 0);

addRemovableToRunTimeSelectionTable
(
    functionObject,
    computeBoundaryLayerThicknessFunctionObject,
    dictionary
);


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

// dynamicCode:
// SHA1 = 60a9df07b0b5e008a71ce1cbe6febd0f14d20114
//
// unique function name that can be checked if the correct library version
// has been loaded
extern "C" void computeBoundaryLayerThickness_60a9df07b0b5e008a71ce1cbe6febd0f14d20114(bool load)
{
    if (load)
    {
        // Code that can be explicitly executed after loading
    }
    else
    {
        // Code that can be explicitly executed before unloading
    }
}


// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //

//{{{ begin localCode

//}}} end localCode

} // End namespace Foam


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const Foam::fvMesh&
Foam::computeBoundaryLayerThicknessFunctionObject::mesh() const
{
    return refCast<const fvMesh>(obr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::
computeBoundaryLayerThicknessFunctionObject::
computeBoundaryLayerThicknessFunctionObject
(
    const word& name,
    const Time& runTime,
    const dictionary& dict
)
:
    functionObjects::regionFunctionObject(name, runTime, dict)
{
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::
computeBoundaryLayerThicknessFunctionObject::
~computeBoundaryLayerThicknessFunctionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool
Foam::
computeBoundaryLayerThicknessFunctionObject::read(const dictionary& dict)
{
    if (false)
    {
        printMessage("read computeBoundaryLayerThickness");
    }

//{{{ begin code
    
//}}} end code

    return true;
}


bool
Foam::
computeBoundaryLayerThicknessFunctionObject::execute()
{
    if (false)
    {
        printMessage("execute computeBoundaryLayerThickness");
    }

//{{{ begin code
    #line 90 "/home/disha/OpenFOAM/disha-v2512/run/Flatplate/Laminar/nasa_validation/trial1/system/controlDict/functions/calculateDelta"
#include <fstream>

            const scalar U_inf = 39.53;
            const scalar u_target = 0.99 * U_inf;

            const List<scalar> x_probes({0.05, 0.10, 0.15, 0.20, 0.25, 0.30});
            
            const scalar y_min = 0.0;
            const scalar y_max = 0.034; // Domain height in meters
            const label nPoints = 200; 

            if (mesh().foundObject<volVectorField>("U"))
            {
                const volVectorField& U = mesh().lookupObject<volVectorField>("U");

                // Save data to case1_delta_vs_x.csv in case directory
                std::ofstream outFile("case1_delta_vs_x.csv");
                outFile << "x_m,delta_m" << std::endl;

                Info<< "\n=============================================" << nl;
                Info<< "  BOUNDARY LAYER THICKNESS (delta) AT 99% U_inf" << nl;
                Info<< "=============================================" << nl;

                for (const scalar x_p : x_probes)
                {
                    scalar delta = 0.0;
                    scalar y_prev = 0.0;
                    scalar u_prev = 0.0;
                    bool found = false;

                    for (label i = 0; i < nPoints; ++i)
                    {
                        scalar y_curr = y_min + i * (y_max - y_min) / (nPoints - 1);
                        point samplePoint(x_p, y_curr, 0.0); 

                        label cellI = mesh().findCell(samplePoint);
                        if (cellI != -1)
                        {
                            scalar u_curr = U[cellI].x();

                            if (u_curr >= u_target && !found)
                            {
                                if (i > 0 && u_curr != u_prev)
                                {
                                    delta = y_prev + (u_target - u_prev) * (y_curr - y_prev) / (u_curr - u_prev);
                                }
                                else
                                {
                                    delta = y_curr;
                                }
                                found = true;
                                break; 
                            }

                            u_prev = u_curr;
                            y_prev = y_curr;
                        }
                    }

                    Info<< "x = " << x_p << " m  -->  delta = " << delta << " m" << nl;
                    outFile << x_p << "," << delta << std::endl;
                }
                Info<< "=============================================\n" << nl;
                outFile.close();
            }
//}}} end code

    return true;
}


bool
Foam::
computeBoundaryLayerThicknessFunctionObject::write()
{
    if (false)
    {
        printMessage("write computeBoundaryLayerThickness");
    }

//{{{ begin code
    
//}}} end code

    return true;
}


bool
Foam::
computeBoundaryLayerThicknessFunctionObject::end()
{
    if (false)
    {
        printMessage("end computeBoundaryLayerThickness");
    }

//{{{ begin code
    
//}}} end code

    return true;
}


// ************************************************************************* //

