export module TwixtCell;

import peg;
using twixt::Peg;

import link;
using twixt::Link;

import <optional>;
import <string>;

namespace twixt {
	export class TwixtCell {
	private:
		std::optional<std::string> color;
		std::optional<Peg&> peg;
		std::optional<Link&> link;
		
	public:
		TwixtCell();
		~TwixtCell();
	};
}