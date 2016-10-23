#ifndef GRAPH_VALUES_CONTROLLER_H
#define GRAPH_VALUES_CONTROLLER_H

#include <escher.h>
#include "../function_store.h"
#include "../evaluate_context.h"
#include "function_title_cell.h"
#include "value_cell.h"
#include "title_cell.h"
#include "interval.h"
#include "abscissa_parameter_controller.h"
#include "derivative_parameter_controller.h"
#include "function_parameter_controller.h"
#include "values_parameter_controller.h"

namespace Graph {

class ValuesController : public HeaderViewController, public TableViewDataSource {
public:
  ValuesController(Responder * parentResponder, FunctionStore * functionStore, EvaluateContext * evaluateContext);

  void setActiveCell(int i, int j);
  int activeRow();
  int activeColumn();
  Interval * interval();
  ValueCell * abscisseCellAtRow(int rowIndex);
  void editValue(bool overwrite, char initialDigit = 0);

  const char * title() const override;
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  ViewController * parameterController();
  int numberOfButtons() const override;
  Button * buttonAtIndex(int index) override;

  int numberOfRows() override;
  int numberOfColumns() override;
  void willDisplayCellAtLocation(View * cell, int i, int j) override;
  KDCoordinate columnWidth(int i) override;
  KDCoordinate rowHeight(int j) override;
  KDCoordinate cumulatedWidthFromIndex(int i) override;
  KDCoordinate cumulatedHeightFromIndex(int j) override;
  int indexFromCumulatedWidth(KDCoordinate offsetX) override;
  int indexFromCumulatedHeight(KDCoordinate offsetY) override;
  View * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  int typeAtLocation(int i, int j) override;

  static constexpr KDCoordinate k_topMargin = 10;
  static constexpr KDCoordinate k_bottomMargin = 5;
  static constexpr KDCoordinate k_leftMargin = 1;
  static constexpr KDCoordinate k_rightMargin = 10;
  static constexpr KDCoordinate k_cellHeight = 30;
  static constexpr KDCoordinate k_abscissaCellWidth = 150;
  static constexpr KDCoordinate k_ordinateCellWidth = 100;

private:
  class ContentView : public View {
    public:
      enum class TableState {
        Empty,
        NonEmpty
      };
      ContentView(View * mainView);
      void drawRect(KDContext * ctx, KDRect rect) const override;
      void setTableState(TableState tableState);
      TableState tableState();
    private:
      PointerTextView m_noFunctionSelected;
      View * m_mainView;
      TableState m_tableState;
      int numberOfSubviews() const override;
      View * subviewAtIndex(int index) override;
      void layoutSubviews() override;
  };

  Function * functionAtColumn(int i);
  bool isDerivativeColumn(int i);
  Responder * tabController() const;
  void configureAbscissa();
  void configureFunction();
  void configureDerivativeFunction();
  constexpr static int k_maxNumberOfCells = 40;
  constexpr static int k_maxNumberOfFunctions = 5;
  // !!! CAUTION: The order here is important
  // The cells should be initialized *before* the TableView!
  TitleCell m_abscissaTitleCell;
  FunctionTitleCell m_functionTitleCells[k_maxNumberOfFunctions];
  ValueCell m_floatCells[k_maxNumberOfCells];
  TableView m_tableView;
  int m_activeCellX;
  int m_activeCellY;
  FunctionStore * m_functionStore;
  EvaluateContext * m_evaluateContext;
  Interval m_interval;
  ValuesParameterController m_parameterController;
  AbscissaParameterController m_abscissaParameterController;
  FunctionParameterController m_functionParameterController;
  DerivativeParameterController m_derivativeParameterController;
  Button m_setIntervalButton;
  ContentView m_contentView;
};

}

#endif