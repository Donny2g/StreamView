#import <UIKit/UIKit.h>



@protocol EKResusableCell <NSObject>

@property (nonatomic, retain) NSString *reuseIdentifier;

@end



@interface EKStreamViewCellInfo : NSObject 

@property (nonatomic, assign) CGRect frame;
@property (nonatomic, assign) NSUInteger index;

// You SHOULD ONLY access this property when this object is in visibleCellInfo!
@property (nonatomic, weak) UIView<EKResusableCell> *cell;

@end
@protocol EAStreamTouchCellDelegate;
@interface EAStreamCell:UIView<EKResusableCell>
{
    NSString *reuseIdentifier;
}

@property (nonatomic) NSInteger index;
@property (nonatomic ,retain) id<EAStreamTouchCellDelegate> touchDelegate;
@end

@protocol EAStreamTouchCellDelegate <NSObject>

- (void)streamCellDidSelected:(NSInteger)index;

@end
@class EKStreamView;


@protocol EKStreamViewDelegate <UIScrollViewDelegate>

- (NSInteger)numberOfCellsInStreamView:(EKStreamView *)streamView;
- (NSInteger)numberOfColumnsInStreamView:(EKStreamView *)streamView;
- (EAStreamCell<EKResusableCell> *)streamView:(EKStreamView *)streamView cellAtIndex:(NSInteger)index;
- (CGFloat)streamView:(EKStreamView *)streamView heightForCellAtIndex:(NSInteger)index;

@optional

- (EAStreamCell *)headerForStreamView:(EKStreamView *)streamView;
- (EAStreamCell *)footerForStreamView:(EKStreamView *)streamView;
- (void)streamView:(EKStreamView *)streamView willDisplayCell:(EAStreamCell<EKResusableCell> *)cell forIndex:(NSInteger)index;
- (void)streamView:(EKStreamView *)streamView didSelectedCellAtIndex:(NSInteger)index;
@optional

@end


@interface EKStreamViewUIScrollViewDelegate : NSObject<UIScrollViewDelegate>
@property (nonatomic, weak) EKStreamView *streamView;

@end

typedef enum {
    EKStreamViewScrollPositionNone,
    EKStreamViewScrollPositionTop,
    EKStreamViewScrollPositionMiddle,
    EKStreamViewScrollPositionBottom
} EKStreamViewScrollPosition;

@interface EKStreamView : UIScrollView<EAStreamTouchCellDelegate>
{
    NSMutableArray
    *cellHeightsByIndex,    // 1d
    *cellHeightsByColumn,   // 2d
    *rectsForCells,         // 2d EKStreamViewCellInfo
    *infoForCells;          // 1d
    
    NSMutableDictionary *cellCache; // reuseIdentifier => NSMutableArray
    NSSet *visibleCellInfo;
    CGFloat columnWidth;
    EKStreamViewUIScrollViewDelegate *delegateObj;
}

@property (nonatomic, weak) id<EKStreamViewDelegate> delegate;
@property (nonatomic, assign) CGFloat columnPadding;
@property (nonatomic, assign) CGFloat cellPadding;

@property (nonatomic, readonly) CGFloat columnWidth;

@property (nonatomic, readonly) UIView *headerView, *footerView;
@property (nonatomic, readonly) UIView *contentView;

- (id<EKResusableCell>)dequeueReusableCellWithIdentifier:(NSString *)identifier;
- (void)reloadData;
- (void)scrollToCellAtIndex:(NSUInteger)index atScrollPosition:(EKStreamViewScrollPosition)scrollPosition animated:(BOOL)animated;
@end
