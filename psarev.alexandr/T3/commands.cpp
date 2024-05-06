#include "commands.hpp"
#include <fstream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <string>

std::ostream& psarev::chooseAreaType(std::vector< Polygon >& polyVec, std::istream& in, std::ostream& out)
{
  std::string type = "";
  in >> type;
  out << std::fixed << std::setprecision(1);

  if (type == "EVEN")
  {
    getEvenArea(polyVec, out);
  }
  else if (type == "ODD")
  {
    getOddArea(polyVec, out);
  }
  else if (type == "MEAN")
  {
    getMeanArea(polyVec, out);
  }
  else
  {
    if (isDigit(type)) {
      size_t numVerts = std::stoi(type);
      getAreaNumVerts(polyVec, out, numVerts);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  return out;
}

std::ostream& psarev::chooseMaxOpt(std::vector< Polygon >& polyVec, std::istream& in, std::ostream& out)
{
  std::string opt = "";
  in >> opt;

  if (opt == "AREA")
  {
    out << std::fixed << std::setprecision(1);
    getMaxArea(polyVec, out);
  }
  else if (opt == "VERTEXES")
  {
    out << std::fixed << std::setprecision(0);
    getMaxVerts(polyVec, out);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  return out;
}

std::ostream& psarev::chooseMinOpt(std::vector< Polygon >& polyVec, std::istream& in, std::ostream& out)
{
  std::string opt = "";
  in >> opt;

  if (opt == "AREA")
  {
    out << std::fixed << std::setprecision(1);
    getMinArea(polyVec, out);
  }
  else if (opt == "VERTEXES")
  {
    out << std::fixed << std::setprecision(0);
    getMinVerts(polyVec, out);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  return out;
}

std::ostream& psarev::chooseCountOpt(std::vector< Polygon >& polyVec, std::istream& in, std::ostream& out)
{
  std::string opt = "";
  in >> opt;

  if (opt == "EVEN")
  {
    countEvenVerts(polyVec, out);
  }
  else if (opt == "ODD")
  {
    countOddVerts(polyVec, out);
  }
  else
  {
    if (isDigit(opt)) {
      size_t numVerts = std::stoi(opt);
      if (numVerts <= 2)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      countSpecVerts(polyVec, out, numVerts);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  return out;
}

using namespace std::placeholders;

std::ostream& psarev::countRects(std::vector< Polygon >& polyVec, std::istream&, std::ostream& out)
{
  out << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(getRects, _1, _2)) << '\n';
  return out;
}

void psarev::getEvenArea(std::vector< Polygon >& polyVec, std::ostream& out)
{
  out << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(plusEvenArea, _1, _2)) << '\n';
}

void psarev::getOddArea(std::vector< Polygon >& polyVec, std::ostream& out)
{
  out << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(plusOddArea, _1, _2)) << '\n';
}

void psarev::getMeanArea(std::vector< Polygon >& polyVec, std::ostream& out)
{
  double areaSum = std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(plusArea, _1, _2)) << '\n';
  out << areaSum / polyVec.size();
}

void psarev::getAreaNumVerts(std::vector< Polygon >& polyVec, std::ostream& out, size_t& numOfVerts)
{
  out << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(plusSameArea, _1, _2, numOfVerts)) << '\n';
}

void psarev::getMaxArea(std::vector < Polygon >& polyVec, std::ostream& out)
{
  std::vector< double > areaVec(polyVec.size());
  std::transform(polyVec.begin(), polyVec.end(), areaVec.begin(), std::bind(getArea, _1));
  double maxArea = *(std::max_element(areaVec.begin(), areaVec.end()));
  out << maxArea << '\n';
}

void psarev::getMinArea(std::vector < Polygon >& polyVec, std::ostream& out)
{
  std::vector< double > areaVec(polyVec.size());
  std::transform(polyVec.begin(), polyVec.end(), areaVec.begin(), std::bind(getArea, _1));
  double minArea = *(std::min_element(areaVec.begin(), areaVec.end()));
  out << minArea << '\n';
}

void psarev::getMaxVerts(std::vector < Polygon >& polyVec, std::ostream& out)
{
  std::vector< int > numsVerts(polyVec.size());
  std::transform(polyVec.begin(), polyVec.end(), numsVerts.begin(), std::bind(getNumVerts, _1));
  int maxNum = *(std::max_element(numsVerts.begin(), numsVerts.end()));
  out << maxNum << '\n';
}

void psarev::getMinVerts(std::vector < Polygon >& polyVec, std::ostream& out)
{
  std::vector< int > numsVerts(polyVec.size());
  std::transform(polyVec.begin(), polyVec.end(), numsVerts.begin(), std::bind(getNumVerts, _1));
  int minNum = *(std::min_element(numsVerts.begin(), numsVerts.end()));
  out << minNum << '\n';
}

void psarev::countEvenVerts(std::vector < Polygon >& polyVec, std::ostream& out)
{
  out << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(getEvenVerts, _1, _2)) << '\n';
}

void psarev::countOddVerts(std::vector < Polygon >& polyVec, std::ostream& out)
{
  out << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(getOddVerts, _1, _2)) << '\n';
}

void psarev::countSpecVerts(std::vector < Polygon >& polyVec, std::ostream& out, size_t& numVerts)
{
  out << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(getSpecVerts, _1, _2, numVerts)) << '\n';
}
