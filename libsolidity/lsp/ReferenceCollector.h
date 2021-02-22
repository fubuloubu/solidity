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

#include <libsolidity/ast/ASTForward.h>
#include <libsolidity/ast/ASTVisitor.h>
#include <libsolidity/lsp/LSPTypes.h>

namespace solidity::lsp
{

class ReferenceCollector: public frontend::ASTConstVisitor
{
private:
	frontend::Declaration const& m_declaration;
	std::string const& m_sourceIdentifierName;
	std::vector<DocumentHighlight> m_result;

public:
	ReferenceCollector(frontend::Declaration const& _declaration, std::string const& _sourceIdentifierName);

	std::vector<DocumentHighlight> take() { return std::move(m_result); }

	static std::vector<DocumentHighlight> collect(
		frontend::Declaration const* _declaration,
		frontend::ASTNode const& _ast,
		std::string const& _sourceIdentifierName = {}
	);

	bool visit(frontend::ImportDirective const& _import) override;
	bool visit(frontend::Identifier const& _identifier) override;
	bool visit(frontend::MemberAccess const& _memberAccess) override;
	bool visitNode(frontend::ASTNode const& _node) override;

private:
	bool tryAddReference(frontend::Declaration const* _declaration, solidity::langutil::SourceLocation const& _location);
	void addReference(solidity::langutil::SourceLocation const& _location);
};

} // end namespace