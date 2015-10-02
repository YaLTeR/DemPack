#include <chrono>
#include <cstdio>
#include <boost/nowide/args.hpp>
#include <boost/nowide/iostream.hpp>

#include "DemoFile.hpp"

using namespace boost;

void usage()
{
	nowide::cerr << "Usage:"
                    "\n\tDemPack <path to demo.dem>"
                    "\n\tDemPack <path to demo.dem> -u"
                    "\n\tDemPack <path to demo.dem> -p <path to output.dem>"
                 << std::endl;
}

int main(int argc, char *argv[])
{
	nowide::args a(argc, argv);

	if (argc != 2 && argc != 3 && argc != 4) {
		usage();
		return 1;
	}

	enum {
		PRINT_AVAILABLE,
		PACK,
		UNPACK
	} op = PRINT_AVAILABLE;

	if (argc == 3) {
		if (argv[2][0] != '-' || argv[2][1] != 'u' || argv[2][2] != '\0') {
			usage();
			return 1;
		}

		op = UNPACK;
	}

	if (argc == 4) {
		if (argv[2][0] != '-' || argv[2][1] != 'p' || argv[2][2] != '\0') {
			usage();
			return 1;
		}

		op = PACK;
	}

	try {
		DemoFile demo(argv[1]);
		demo.ReadFrames();

		size_t byte_count = 0;
		bool done = false;

		for (auto& entry : demo.directoryEntries) {
			for (auto& frame : entry.frames) {
				// If it's a netmsg frame:
				if (frame->type < DemoFrameType::DEMO_START || frame->type > DemoFrameType::DEMO_BUFFER) {
					NetMsgFrame *f = reinterpret_cast<NetMsgFrame*>(frame.get());
					switch (op) {
					case PRINT_AVAILABLE:
						byte_count += 4;
						break;

					case PACK:
						if (std::fread(&f->DemoInfo.UserCmd.align_1, sizeof(f->DemoInfo.UserCmd.align_1), 1, stdin) == 0) {
							done = true;
							break;
						}
						byte_count++;

						if (std::fread(&f->DemoInfo.UserCmd.align_2, sizeof(f->DemoInfo.UserCmd.align_2), 1, stdin) == 0) {
							done = true;
							break;
						}
						byte_count++;

						if (std::fread(&f->DemoInfo.UserCmd.align_3, sizeof(f->DemoInfo.UserCmd.align_3), 1, stdin) == 0) {
							done = true;
							break;
						}
						byte_count++;

						if (std::fread(&f->DemoInfo.UserCmd.align_4, sizeof(f->DemoInfo.UserCmd.align_4), 1, stdin) == 0) {
							done = true;
							break;
						}
						byte_count++;

						break;

					case UNPACK:
						nowide::cout << f->DemoInfo.UserCmd.align_1 << f->DemoInfo.UserCmd.align_2 << f->DemoInfo.UserCmd.align_3 << f->DemoInfo.UserCmd.align_4;
						byte_count += 4;
						break;
					}
				}

				if (done)
					break;
			}

			if (done)
				break;
		}

		if (op == PACK)
			demo.Save(argv[3]);

		if (op != UNPACK)
			nowide::cout << byte_count << std::endl;
	} catch (const std::exception& ex) {
		nowide::cerr << "Error: " << ex.what() << std::endl;
	}

	return 0;
}
