//
//  SGVideoCapture.h
//  SGMediaKit
//
//  Created by Single on 23/11/2016.
//  Copyright © 2016 single. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SGVideoConfiguration.h"

FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameNone;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameCameraDisable;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNmaeCameraPositionDisable;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameLockCameraFailure;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameTorchDisable;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameFocusDisable;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameFocusModeUnsupported;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameExposureDisable;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameExposureModeUnsupported;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameHasStartRecord;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameFileURLInvalid;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameFileExists;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameFileDirectoryInexistence;
FOUNDATION_EXTERN NSString * const SGVideoCaptureErrorNameRecordCanceled;

typedef NS_ENUM(NSUInteger, SGVideoCaptureErrorCode) {
    SGVideoCaptureErrorCodeNone = 0x00,
    SGVideoCaptureErrorCodeCameraDisable = 0xFF,
    SGVideoCaptureErrorCodeCameraPositionDisable,
    SGVideoCaptureErrorCodeLockCameraFailure,
    SGVideoCaptureErrorCodeTorchDisable,
    SGVideoCaptureErrorCodeFocusDisable,
    SGVideoCaptureErrorCodeFocusModeUnsupported,
    SGVideoCaptureErrorCodeExposureDisable,
    SGVideoCaptureErrorCodeExposureModeUnsupported,
    SGVideoCaptureErrorCodeHasStartRecord = 0xFFFF,
    SGVideoCaptureErrorCodeFileURLInvalid,
    SGVideoCaptureErrorCodeFileExists,
    SGVideoCaptureErrorCodeFileDirectoryInexistence,
    SGVideoCaptureErrorCodeRecordCanceled,
};

typedef NS_ENUM(NSUInteger, SGCameraPosition) {
    SGCameraPositionFront,
    SGCameraPositionBack,
};

typedef NS_ENUM(NSUInteger, SGFocusMode) {
    SGFocusModeAutomatic,
    SGFocusModeManual,
};

typedef NS_ENUM(NSUInteger, SGExposureMode) {
    SGExposureModeAutomatic,
    SGExposureModeManual,
};

@class SGVideoCapture;

@protocol SGVideoCaptureDelegate <NSObject>

@required;
- (void)videoCapture:(SGVideoCapture *)videoCapture needForceFinishRecordingForFileURL:(NSURL *)fileURL;

@optional;
- (void)videoCaptureUpdateMetadata:(SGVideoCapture *)videoCapture;

- (void)videoCaptureWillStartRunning:(SGVideoCapture *)videoCapture;
- (void)videoCaptureDidStartRunning:(SGVideoCapture *)videoCapture;
- (void)videoCaptureWillStopRunning:(SGVideoCapture *)videoCapture;
- (void)videoCaptureDidStopRunning:(SGVideoCapture *)videoCapture;

- (void)videoCapture:(SGVideoCapture *)videoCapture willStartRecordingfToFileURL:(NSURL *)fileURL;
- (void)videoCapture:(SGVideoCapture *)videoCapture didStartRecordingToFileURL:(NSURL *)fileURL;
- (void)videoCapture:(SGVideoCapture *)videoCapture willFinishRecordingToFileURL:(NSURL *)fileURL;
- (void)videoCapture:(SGVideoCapture *)videoCapture didFinishRecordingToFileURL:(NSURL *)fileURL;
- (void)videoCapture:(SGVideoCapture *)videoCapture willCancelRecordingToFileURL:(NSURL *)fileURL;
- (void)videoCapture:(SGVideoCapture *)videoCapture didCancelRecordingToFileURL:(NSURL *)fileURL;

- (void)videoCapture:(SGVideoCapture *)videoCapture outputPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

@interface SGVideoCapture : NSObject

+ (BOOL)canCapture;     // check whether the camera is available. if no camera available, return NO.

+ (instancetype)new UNAVAILABLE_ATTRIBUTE;
- (instancetype)init UNAVAILABLE_ATTRIBUTE;

- (instancetype)initWithVideoConfiguration:(SGVideoConfiguration *)videoConfiguration NS_DESIGNATED_INITIALIZER;

@property (nonatomic, assign, readonly) BOOL running;
@property (nonatomic, assign, readonly) BOOL recording;
@property (nonatomic, weak) id <SGVideoCaptureDelegate> delegate;
@property (nonatomic, strong, readonly) UIView * view;
@property (nonatomic, assign) BOOL mirror;
@property (nonatomic, assign) BOOL autorotate;      // default is YES;

@property (nonatomic, assign, readonly) SGCameraPosition cameraPosition;   // default is back. if device is unsupported back camera, it's will be front.
@property (nonatomic, assign, readonly) BOOL cameraPositionFrontEnable;
@property (nonatomic, assign, readonly) BOOL cameraPositionBackEnable;
- (BOOL)setCameraPosition:(SGCameraPosition)cameraPosition error:(NSError **)error;

@property (nonatomic, assign, readonly) BOOL torch;   // default is off
@property (nonatomic, assign, readonly) BOOL torchEnable;
- (BOOL)setTorch:(BOOL)torch error:(NSError **)error;

@property (nonatomic, assign, readonly) SGFocusMode focusMode;
@property (nonatomic, assign, readonly) BOOL focusModeEnable;
- (BOOL)setFocusMode:(SGFocusMode)focusMode error:(NSError **)error;
- (BOOL)setFocusPointOfInterest:(CGPoint)focusPointOfInterest error:(NSError **)error;

@property (nonatomic, assign, readonly) SGExposureMode exposureMode;
@property (nonatomic, assign, readonly) BOOL exposureModeEnable;
- (BOOL)setExposureMode:(SGExposureMode)exposureMode error:(NSError **)error;
- (BOOL)setExposurePointOfInterest:(CGPoint)exposurePointOfInterest error:(NSError **)error;

- (void)startRunning;
- (void)stopRunning;

- (BOOL)startRecordingWithFileURL:(NSURL *)fileURL error:(NSError **)error finishedHandler:(void (^)(NSURL * fileURL, NSError * error))finishedHandler;
- (void)finishRecording;
- (void)cancelRecording;

@end
