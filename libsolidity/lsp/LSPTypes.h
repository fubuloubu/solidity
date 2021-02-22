/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
// SPDX-License-Identifier: GPL-3.0
#pragma once

#include <libsolidity/lsp/Range.h>
#include <string>

namespace solidity::lsp
{

enum class Trace { Off, Messages, Verbose };

struct WorkspaceFolder {
	std::string name; // The name of the workspace folder. Used to refer to this workspace folder in the user interface.
	std::string path; // The associated file path for this workspace folder.
};

struct DocumentPosition {
	std::string path;
	Position position;
};

struct ServerId {
	std::string serverName;
	std::string serverVersion;
};

enum class DocumentHighlightKind {
	Unspecified,
	Text,           //!< a textual occurrence
	Read,           //!< read access to a variable
	Write,          //!< write access to a variable
};

struct Location {
	std::string path;
	Range range;
};

struct DocumentHighlight {
	Range range;
	DocumentHighlightKind kind = DocumentHighlightKind::Unspecified;
};

enum class DiagnosticSeverity {
	Error = 1,
	Warning = 2,
	Information = 3,
	Hint = 4,
};

enum class DiagnosticTag {
	Unnecessary = 1, // Unused or unnecessary code.
	Deprecated = 2   // Deprecated or obsolete code.
};

/// Represents a related message and source code location for a diagnostic. This should be
/// used to point to code locations that cause or related to a diagnostics, e.g when duplicating
/// a symbol in a scope.
struct DiagnosticRelatedInformation {
	Location location;   // The location of this related diagnostic information.
	std::string message; // The message of this related diagnostic information.
};

/// Represents a diagnostic, such as a compiler error or warning. Diagnostic objects are only valid in the scope of a resource.
struct Diagnostic {
	Range range;                                   // The range at which the message applies.
	std::optional<DiagnosticSeverity> severity;
	std::optional<unsigned long long> code;        // The diagnostic's code, which might appear in the user interface.
	std::optional<std::string> source;             // A human-readable string describing the source of this diagnostic, e.g. 'typescript' or 'super lint'.
	std::string message;                           // The diagnostic's message.
	std::vector<DiagnosticTag> diagnosticTag;      // Additional metadata about the diagnostic.
	std::vector<DiagnosticRelatedInformation> relatedInformation; // An array of related diagnostic information, e.g. when symbol-names within a scope collide all definitions can be marked via this property.
};

}