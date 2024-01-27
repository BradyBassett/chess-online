import type { Metadata } from "next";

import "../styles/globals.scss";


export const metadata: Metadata = {
	title: "Chess Online",
	description: "Simple web based chess application",
}

export default function RootLayout({
	children,
}: {
	children: React.ReactNode
}): React.ReactElement {
	return (
		<html lang="en">
			<body>{children}</body>
		</html>
	);
}
