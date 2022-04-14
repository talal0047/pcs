#include "pcs/operation/label.h"

#include <string>
#include <memory>
#include <optional>

#include "pcs/operation/operation.h"
#include "pcs/operation/transfer.h"
#include "pcs/operation/nop.h"

namespace pcs {

	std::unique_ptr<IOperation> StringToOperation(const std::string& label) {
		if (label.find("in:") != std::string::npos) {
			return std::make_unique<TransferOperation>(Transfer::in, stoull(label.substr(3)));
		}
		else if (label.find("out:") != std::string::npos) {
			return std::make_unique<TransferOperation>(Transfer::out, stoull(label.substr(4)));
		}
		else if (label == "nop") {
			return std::make_unique<Nop>();
		}
		return std::make_unique<Operation>(label);
	}

	std::optional<TransferOperation> StringToTransfer(const std::string& label) {
		if (label.find("in:") != std::string::npos) {
			return TransferOperation(Transfer::in, stoull(label.substr(3)));
		} else if (label.find("out:") != std::string::npos) {
			return TransferOperation(Transfer::out, stoull(label.substr(4)));
		}
		return {};
	}

}