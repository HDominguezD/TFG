/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkRectilinearGridOutlineFilter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkRectilinearGridOutlineFilter
 * @brief   create wireframe outline for a rectilinear grid.
 *
 * vtkRectilinearGridOutlineFilter works in parallel.  There is no reason.
 * to use this filter if you are not breaking the processing into pieces.
 * With one piece you can simply use vtkOutlineFilter.  This filter
 * ignores internal edges when the extent is not the whole extent.
*/

#ifndef vtkRectilinearGridOutlineFilter_h
#define vtkRectilinearGridOutlineFilter_h

#include "vtkFiltersParallelModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

class VTKFILTERSPARALLEL_EXPORT vtkRectilinearGridOutlineFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkRectilinearGridOutlineFilter *New();
  vtkTypeMacro(vtkRectilinearGridOutlineFilter,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

protected:
  vtkRectilinearGridOutlineFilter() {}
  ~vtkRectilinearGridOutlineFilter() override {}
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;
  int RequestInformation(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;
  int FillInputPortInformation(int port, vtkInformation *info) override;

private:
  vtkRectilinearGridOutlineFilter(const vtkRectilinearGridOutlineFilter&) = delete;
  void operator=(const vtkRectilinearGridOutlineFilter&) = delete;
};

#endif
