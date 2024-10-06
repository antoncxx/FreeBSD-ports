PORTNAME=          pfSense-pkg-wallmon
PORTVERSION=       0.1.0
PORTREVISION=      1
CATEGORIES=        security
MASTER_SITES=      https://github.com/NullNet-ai/wallmon/archive/ref/tags/
DISTFILES=         v${PORTVERSION}.tar.gz

MAINTAINER=        anton.liashkevich.eng@gmail.com
COMMENT=           pfSense package wallmon
WWW=               https://todo.com

LICENSE=           BSD2CLAUSE

USES=              gmake
ALL_TARGET=        release

WRKSRC=            ${WRKDIR}/wallmon-${PORTVERSION}

SUB_FILES=         pkg-install pkg-deinstall
SUB_LIST=          PORTNAME=${PORTNAME}

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/pkg
	${MKDIR} ${STAGEDIR}${DATADIR}
	${MKDIR} ${STAGEDIR}/etc/inc/priv
	${INSTALL_DATA} ${FILESDIR}${PREFIX}/pkg/wallmon.inc ${STAGEDIR}${PREFIX}/pkg
	${INSTALL_DATA} ${FILESDIR}${PREFIX}/pkg/wallmon.xml ${STAGEDIR}${PREFIX}/pkg
	${INSTALL_DATA} ${FILESDIR}/etc/inc/priv/wallmon.priv.inc \
		${STAGEDIR}/etc/inc/priv
	${INSTALL_DATA} ${FILESDIR}${DATADIR}/info.xml ${STAGEDIR}${DATADIR}
	@${REINPLACE_CMD} -i '' -e "s|%%PKGVERSION%%|${PKGVERSION}|" \
		${STAGEDIR}${DATADIR}/info.xml \
		${STAGEDIR}${PREFIX}/pkg/wallmon.xml

	${INSTALL_PROGRAM} ${WRKSRC}/wallmon ${STAGEDIR}${PREFIX}/bin/

.include <bsd.port.mk>

