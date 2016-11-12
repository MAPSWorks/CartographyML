#include <QMetaObject>

#include <mapnik/symbolizer_enumerations.hpp>

#define DE(N) N = mapnik::N

struct MapnikEnums
{
  Q_GADGET
public:
  enum LineCapEnum
  {
    DE(BUTT_CAP), DE(SQUARE_CAP), DE(ROUND_CAP)
  };
  Q_ENUM(LineCapEnum)
  enum LineJoinEnum
  {
    DE(MITER_JOIN), DE(MITER_REVERT_JOIN), DE(ROUND_JOIN), DE(BEVEL_JOIN)
  };
  Q_ENUM(LineJoinEnum)
  enum LineRasterizerEnum
  {
    DE(RASTERIZER_FULL), DE(RASTERIZER_FAST)
  };
  Q_ENUM(LineRasterizerEnum)
  enum HaloRasterizerEnum
  {
    DE(HALO_RASTERIZER_FULL), DE(HALO_RASTERIZER_FAST)
  };
  Q_ENUM(HaloRasterizerEnum)
  enum PointPlacementEnum
  {
    DE(CENTROID_POINT_PLACEMENT), DE(INTERIOR_POINT_PLACEMENT)
  };
  Q_ENUM(PointPlacementEnum)
  enum PatternAlignmentEnum
  {
    DE(LOCAL_ALIGNMENT), DE(GLOBAL_ALIGNMENT)
  };
  Q_ENUM(PatternAlignmentEnum)
  enum DebugSymbolizerModeEnum
  {
    DE(DEBUG_SYM_MODE_COLLISION), DE(DEBUG_SYM_MODE_VERTEX), DE(DEBUG_SYM_MODE_RINGS)
  };
  Q_ENUM(DebugSymbolizerModeEnum)
  enum MarkerPlacementEnum
  {
    DE(MARKER_POINT_PLACEMENT), DE(MARKER_INTERIOR_PLACEMENT), DE(MARKER_LINE_PLACEMENT), DE(MARKER_VERTEX_FIRST_PLACEMENT), DE(MARKER_VERTEX_LAST_PLACEMENT)
  };
  Q_ENUM(MarkerPlacementEnum)
  enum MarkerMultiPolicyEnum
  {
    DE(MARKER_EACH_MULTI), DE(MARKER_WHOLE_MULTI), DE(MARKER_LARGEST_MULTI)
  };
  Q_ENUM(MarkerMultiPolicyEnum)
  enum TextTransformEnum
  {
    DE(NONE), DE(UPPERCASE), DE(LOWERCASE), DE(CAPITALIZE), DE(REVERSE)
  };
  Q_ENUM(TextTransformEnum)
  enum LabelPlacementEnum
  {
    DE(POINT_PLACEMENT), DE(LINE_PLACEMENT), DE(VERTEX_PLACEMENT), DE(INTERIOR_PLACEMENT)
  };
  Q_ENUM(LabelPlacementEnum)
  enum VerticalAlignmentEnum
  {
    DE(V_TOP), DE(V_MIDDLE), DE(V_BOTTOM), DE(V_AUTO)
  };
  Q_ENUM(VerticalAlignmentEnum)
  enum HorizontalAlignmentEnum
  {
    DE(H_LEFT), DE(H_MIDDLE), DE(H_RIGHT), DE(H_AUTO), DE(H_ADJUST)
  };
  Q_ENUM(HorizontalAlignmentEnum)
  enum JustifyAlignmentEnum
  {
    DE(J_LEFT), DE(J_MIDDLE), DE(J_RIGHT), DE(J_AUTO)
  };
  Q_ENUM(JustifyAlignmentEnum)
  enum TextUprightEnum
  {
    DE(UPRIGHT_AUTO), DE(UPRIGHT_AUTO_DOWN), DE(UPRIGHT_LEFT), DE(UPRIGHT_RIGHT), DE(UPRIGHT_LEFT_ONLY), DE(UPRIGHT_RIGHT_ONLY)
  };
  Q_ENUM(TextUprightEnum)
  enum DirectionEnum
  {
    DE(DIRECTION_LEFT), DE(DIRECTION_RIGHT), DE(DIRECTION_LEFT_ONLY), DE(DIRECTION_RIGHT_ONLY), DE(DIRECTION_AUTO), DE(DIRECTION_AUTO_DOWN), DE(DIRECTION_UP), DE(DIRECTION_DOWN)
  };
  Q_ENUM(DirectionEnum)
  enum GammaMethodEnum
  {
    DE(GAMMA_POWER), DE(GAMMA_LINEAR), DE(GAMMA_NONE), DE(GAMMA_THRESHOLD), DE(GAMMA_MULTIPLY)
  };
  Q_ENUM(GammaMethodEnum)
private:
  MapnikEnums() = delete;
  ~MapnikEnums() = delete;
};