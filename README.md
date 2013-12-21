StreamView
==========

This is a project about streamView.iOS 6 introduced a new feature called UICollectionView.This class can instead of most function of the UICollectionView.And make a view like a  stream in it.

Prerequisite
ARC
iOS 4.3+,

How to Use

Step 1

There are five properties for you to set up.

@property (nonatomic, assign) CGFloat columnPadding;   //Spacing between items vertically

@property (nonatomic, assign) CGFloat cellPadding;    //Spacing between items horizontal

@property (nonatomic, readonly) UIView *headerView, *footerView;   //you can design your custom headerView or footerView

/*
   this view is a container which containing all cells,headerView and footerView
*/
@property (nonatomic, readonly) UIView *contentView;  

Step 2

And you also need to implement one method in your delegate for the EKStreamViewDelegate protocol.Just like UITableViewDelegate

 - (NSInteger)numberOfCellsInStreamView:(EKStreamView *)streamView;
 - (NSInteger)numberOfColumnsInStreamView:(EKStreamView *)streamView;
 - (EAStreamCell<EKResusableCell> *)streamView:(EKStreamView *)streamView cellAtIndex:(NSInteger)index;
 - (CGFloat)streamView:(EKStreamView *)streamView heightForCellAtIndex:(NSInteger)index;

Also,you may want to expand the EAStreamCell,don't forget set reuseIdentifier in streamView:(EKStreamView *)streamView cellAtIndex:(NSInteger)index.And I recommend you do like this.

 - (UIView *)streamView:(EKStreamView *)streamView cellAtIndex:(NSInteger)index
{
    static NSString *CellID1 = @"MyCell1";
    YourCell *cell;
    cell = (YourCell *)[streamView dequeueReusableCellWithIdentifier:CellID];
     CGFloat destWidth = (streamView.bounds.size.width - (kNumberOfColumns + 1) * streamView.columnPadding) / kNumberOfColumns;
    if (cell == nil) {
        
        cell = [[YourCell alloc] initWithFrame:CGRectMake(0, 0, 100, 100) infoViewHeight:kViewInfoHeight] ;
        cell.reuseIdentifier = CellID;
    }
    
    CGFloat destHeight = [self streamView:streamView cellAtIndex:index];
    cell.contentView.frame = CGRect(0,0,destWidth,destHeight);

    return cell;
}

 - (CGFloat)streamView:(EKStreamView *)streamView heightForCellAtIndex:(NSInteger)index
{
    CGFloat heigt = 0;
    switch (index % kNumberOfColumns) {
        case 0:
            //set height value
            break;
        default:
            break;
    }
    return height;
}

Step 3 (Optional)
 - (EAStreamCell *)headerForStreamView:(EKStreamView *)streamView;
 - (EAStreamCell *)footerForStreamView:(EKStreamView *)streamView;
 - (void)streamView:(EKStreamView *)streamView willDisplayCell:(EAStreamCell<EKResusableCell> *)cell forIndex:(NSInteger)index;
 - (void)streamView:(EKStreamView *)streamView didSelectedCellAtIndex:(NSInteger)index;

these method provide some function you may want.Similarly like UITableViewDelegate,right?

Limitation

Only one section is supported.
Only vertical scrolling is supported.


License

StreamView is available under the MIT license. See the LICENSE file for more info.
