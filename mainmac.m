#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>

#include <stdio.h>
#include <unistd.h>

#include "texture.h"
#include "global.h"
#include "shader.h"
#include "geometry.h"

static Texture *texture1;
static Texture *texture2;

static void Display(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawTexture(texture2, 1.0);
	DrawTexture(texture1, 1.0);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	DrawQuad(50, 50, 500, 500);
}

@interface JK2DOpenGLView : NSOpenGLView
@end

@implementation JK2DOpenGLView

- (void)prepareOpenGL {
	[super prepareOpenGL];
	[[self openGLContext] makeCurrentContext];
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	texture1 = BindTexture("bg_day.png", 0, 0, 288, 512, 80, 80, 368, 592);
	texture2 = BindTexture("test2.png", 0, 0, 200, 200, 0, 0, 200, 200);
	if (texture1 == NULL || texture2 == NULL) {
		fprintf(stderr, "Could not load bundled PNG resources.\n");
	}
}

- (void)reshape {
	[super reshape];
	NSRect bounds = [self bounds];
	SetWH((int)bounds.size.width, (int)bounds.size.height);
	[[self openGLContext] makeCurrentContext];
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());
}

- (void)drawRect:(NSRect)dirtyRect {
	(void)dirtyRect;
	[[self openGLContext] makeCurrentContext];
	if (texture1 != NULL && texture2 != NULL) {
		Display();
	}
	[[self openGLContext] flushBuffer];
}

@end

@interface JK2DAppDelegate : NSObject <NSApplicationDelegate>
@property(nonatomic, strong) NSWindow *window;
@property(nonatomic, strong) NSTimer *timer;
@end

@implementation JK2DAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
	(void)notification;
	SetWH(800, 600);
	NSOpenGLPixelFormatAttribute attributes[] = {
		NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersionLegacy,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize, 24,
		0
	};
	NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
	JK2DOpenGLView *view = [[JK2DOpenGLView alloc] initWithFrame:NSMakeRect(0, 0, 800, 600)
									 pixelFormat:format];
	self.window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 800, 600)
								 styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable)
								   backing:NSBackingStoreBuffered
									 defer:NO];
	[self.window setTitle:@"jk2d"];
	[self.window setContentView:view];
	[self.window makeKeyAndOrderFront:nil];
	self.timer = [NSTimer scheduledTimerWithTimeInterval:1.0 / 30.0
										 target:view selector:@selector(setNeedsDisplay:)
										 userInfo:nil repeats:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
	(void)sender;
	return YES;
}

@end

int main(int argc, const char *argv[]) {
	@autoreleasepool {
		(void)argc;
		(void)argv;
		NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
		if (resourcePath != nil) {
			chdir([resourcePath fileSystemRepresentation]);
		}
		NSApplication *application = [NSApplication sharedApplication];
		JK2DAppDelegate *delegate = [[JK2DAppDelegate alloc] init];
		[application setDelegate:delegate];
		[application run];
	}
	return 0;
}
